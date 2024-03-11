//4112054022 董哲睿
#include <Wire.h>
#include <Arduino.h>
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);
const byte trigPin =4;
const byte echoPin =5;
const byte SW=13;
boolean button;
boolean up=1;
int times;

void setup(){
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(SW,INPUT);
  pinMode(12,OUTPUT);
}

void loop(){
  lcd.setBacklight(255);
  lcd.clear();
  button=digitalRead(SW);
  times=0;
  while(button==false){
    for(int counter=60;counter>0;counter=counter-0.5){
      lcd.setCursor(0,0);
      if(counter%1==0){
        lcd.print(counter);
        lcd.println("sec");
      }
      float dur,dis;
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(1000);
      digitalWrite(trigPin,LOW);
      dur= pulseIn(echoPin,HIGH);
      dis=dur/58.8;
      if(up==1){
        if(dis<=10){
        times=times+1;
        up=0;
          if(times==1){
            lcd.setCursor(0,1);
            lcd.print(times);
            lcd.println(" time");
          }
          else if(times>>1){
            lcd.setCursor(0,1);
            lcd.print(times);
            lcd.println(" times");
          }
        }
      }
      if(dis>=20){
        up=1;
      }
      if(counter<=10){
        digitalWrite(12,HIGH);
        delay(950);
        digitalWrite(12,LOW);
      }
      else if (counter>10){
        delay(950);
      }
      Serial.println(up);
    }
    lcd.setCursor(0,0);
    if(times==1){
      lcd.print("You have done ");
      lcd.setCursor(0,1);
      lcd.print(times);
      lcd.println(" time");
    }
    else if(times>1){
      lcd.print("You have done ");
      lcd.setCursor(0,1);
      lcd.print(times);
      lcd.println(" times");
    }
    delay(30000);
    button=digitalRead(SW);
  } 
}
    

    
    
  
 
  



