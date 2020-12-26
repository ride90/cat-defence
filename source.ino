#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define USE_GUN true
#define CALIBRATION_TIME_SECS 20
#define OUTPUT_PIN_GUN 8
#define INPUT_PIN_PIR1 10
#define INPUT_PIN_PIR2 11
#define LCD_SERIAL_ADDRESS 0x27
#define LCD_LINES 2
#define LCD_CHARS 16

int shots = 0;

// PIR
int pir1State = LOW;
int pir2State = LOW;
// LCD
LiquidCrystal_I2C lcd(LCD_SERIAL_ADDRESS, LCD_CHARS, LCD_LINES);


void setup() {
  // Serial.begin(9600);
  // pins
  pinMode(OUTPUT_PIN_GUN, OUTPUT);
  pinMode(INPUT_PIN_PIR1, INPUT);
  pinMode(INPUT_PIN_PIR2, INPUT);
  // default states
  digitalWrite(OUTPUT_PIN_GUN, LOW);
  // LCD
  setupLCD();
  // PIRs
  setupPIR();
}


void setupLCD() {
  lcd.init();
  lcd.backlight();
}


void setupPIR() {
  // give a sensors some time to calibrate
  lcd.setCursor(0, 0);
  lcd.print("Calibrating");
  lcd.setCursor(0, 1);
  lcd.print("sensors...");
  delay(1000 * CALIBRATION_TIME_SECS);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibration");
  lcd.setCursor(0, 1);
  lcd.print("is done!");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Let's make them");
  lcd.setCursor(0, 1);
  lcd.print("wet...");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Shots: ");
  lcd.print(shots);
  delay(1000);
}


void shot() {
   if (!USE_GUN) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BASTARD DETECTED");
      delay(8000);
      return;
   }

  digitalWrite(OUTPUT_PIN_GUN, HIGH);
  delay(1600);
  digitalWrite(OUTPUT_PIN_GUN, LOW);
  delay(500);
  digitalWrite(OUTPUT_PIN_GUN, HIGH);
  delay(1600);
  digitalWrite(OUTPUT_PIN_GUN, LOW);
  delay(4000);
}


void loop(){
  pir1State = digitalRead(INPUT_PIN_PIR1);
  pir2State = digitalRead(INPUT_PIN_PIR2);

  if (pir1State == HIGH || pir2State == HIGH) {
    shot();
    shots++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Shots: ");
    lcd.print(shots);
  }
  delay(1000);
} 
