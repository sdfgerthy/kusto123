#include <Servo.h>
#include <GyverStepper2.h>
GStepper2<STEPPER4WIRE> stepper_caret(200, 9, 10, 11, 12);
GStepper2<STEPPER4WIRE> stepper_belt(200, 22, 24, 26, 28);

Servo servo_1;
Servo servo_2;
Servo servo_3;

int echoPin = 53;
int trigPin = 51;
int duration, dist;
int dist_min = 2; // минимальное расстояние до стакана в см
int dist_max = 7; // максимальное
int drinks[] = {0, 0, 0, 0};
byte count = 0;
boolean servo_flag = 0;
boolean tmr_flag=0;
boolean caret_flag=0;

boolean butt_flag_1=0;
boolean butt_flag_2=0;
boolean butt_flag_3=0;
boolean butt_flag_4=0;
boolean butt_flag_5=0;
boolean butt_flag_6=0;
boolean butt_flag_7=0;

boolean valve_flag_1=0;
boolean valve_flag_2=0;
boolean valve_flag_3=0;
boolean valve_flag_4=0;
boolean valve_flag_5=0;
boolean valve_flag_6=0;
boolean FLAG=0;
int sum_flags;
unsigned long last_press;
unsigned long tmr;
unsigned long pour_time = 2000; // время наливания 5 мл жидкости
int h = 0; //дом
int next = -34;//кол-во шагов степпера между двумя стаканами 42,5
unsigned long time_1 = 10*pour_time;
  unsigned long time_2 = 2*pour_time;
  unsigned long time_3 = 8*pour_time;
  unsigned long time_4 = 16*pour_time;
  unsigned long time_5 = 4*pour_time;
  unsigned long time_6 = 6*pour_time;
  unsigned long time_7 = 10*pour_time;
  unsigned long time_8 = 7*pour_time;
  unsigned long time_9 = 9*pour_time;
  unsigned long time_10 = 2*pour_time;

void setup(){ 
  Serial.begin(9600); 
  servo_1.attach(31);
  servo_2.attach(32);
  servo_3.attach(33); 
  pinMode(8, INPUT_PULLUP);  
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);  
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);  
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  stepper_caret.setMaxSpeed(50);
  stepper_caret.setAcceleration(50);
  stepper_belt.setMaxSpeed(50);
  stepper_belt.setAcceleration(50);
}

void loop(){
  //кнопки
  boolean butt_1 = !digitalRead(8);  
  boolean butt_2 = !digitalRead(7);
  boolean butt_3 = !digitalRead(6);  
  boolean butt_4 = !digitalRead(5);
  boolean butt_5 = !digitalRead(4);  
  boolean butt_6 = !digitalRead(3); 
  boolean butt_7 = !digitalRead(2); 
  
  //шаговики
  stepper_caret.tick();
  stepper_belt.tick();
  
  //дальномер
  if (millis() - last_press > 30){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist = duration / 58;
    last_press = millis();
  }
  
  //пункт приёма и выдачи заказов
  if ((butt_7==1 || count>3) && butt_flag_7==0 && millis() - last_press > 50){
    butt_flag_7=!butt_flag_7;
    last_press=millis();
  }
  //кнопки
  //пункт приёма и выдачи заказов
  if ((butt_7==1 || count>3) && butt_flag_7==0 && millis() - last_press > 50){
    butt_flag_7=!butt_flag_7;
    last_press=millis();
  }
  //кнопкa 1
  if (butt_1 == 1 && butt_flag_1==0 && butt_flag_7==0){    
    butt_flag_1=1;
  }    
  if (butt_1==0 && butt_flag_1==1 && count<4 && millis() - last_press > 50 && butt_flag_7==0){
    butt_flag_1=0;    
    drinks[count] = 1;
    count+=1;
    Serial.println(count);
    last_press=millis();
  }
  // кнопка 2
  if (butt_2 == 1 && butt_flag_2==0 && butt_flag_7==0){    
    butt_flag_2=1;
  }    
  if (butt_2==0 && butt_flag_2==1 && count<4 && millis() - last_press > 50 && butt_flag_7==0){
    butt_flag_2=0;    
    drinks[count] = 2;
    count+=1;
    Serial.println(count);
    last_press=millis();
  }
  // кнопка 3
  if (butt_3 == 1 && butt_flag_3==0 && butt_flag_7==0){    
    butt_flag_3=1;
  }    
  if (butt_3==0 && butt_flag_3==1 && count<4 && millis() - last_press > 50 && butt_flag_7==0){
    butt_flag_3=0;    
    drinks[count] = 3;
    count+=1;
    Serial.println(count);
    last_press=millis();
  }
  // кнопка 4
  if (butt_4 == 1 && butt_flag_4==0 && butt_flag_7==0){    
    butt_flag_4=1;
  }    
  if (butt_4==0 && butt_flag_4==1 && count<4 && millis() - last_press > 50 && butt_flag_7==0){
    butt_flag_4=0;    
    drinks[count] = 4;
    count+=1;
    Serial.println(count);
    last_press=millis();
  }
  //кнопка 5
  if (butt_5 == 1 && butt_flag_5==0 && butt_flag_7==0){    
    butt_flag_5=1;
  }    
  if (butt_5==0 && butt_flag_5==1 && count<4 && millis() - last_press > 50 && butt_flag_7==0){
    butt_flag_5=0;    
    drinks[count] = 5;
    count+=1;
    Serial.println(count);
    last_press=millis();
  }
  //кнопка 6
  if (butt_6 == 1 && butt_flag_6==0 && butt_flag_7==0){    
    butt_flag_6=1;
  }    
  if (butt_6==0 && butt_flag_6==1 && count<4 && millis() - last_press > 50 && butt_flag_7==0){
    butt_flag_6=0;    
    drinks[count] = 6;
    count+=1;
    Serial.println(count);
    last_press=millis();
  }
  //======== каретка с диспенсером ========
  if (butt_flag_7==1 && caret_flag == 0){
      if (tmr_flag==0){
        tmr=millis();
        tmr_flag=1;
        stepper_caret.setTarget(h); //h это положение домой
      }
      for(int k = 0;k < 4; k++){
        //каретка около первого стакана
        //для каждого из 6 напитков свои пропорции
        //если стакан есть, каретка приехала, другие клапаны закрыты
        sum_flags = valve_flag_1 + valve_flag_2 + valve_flag_3 + valve_flag_4 + valve_flag_5 + valve_flag_6;
        
        
        //====Газированная вода (50 мл.)====
        if (drinks[k]==1 && stepper_caret.ready() == true && (sum_flags == 0 || valve_flag_1 == 1)){
          //valve(servo_1, valve_flag_1, 1, pour_time*10);
          if (valve_flag_1 == 0 && dist > dist_min && dist < dist_max){
            servo_1.write(90);
            valve_flag_1 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_1 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_1.write(0);
            time_1 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==pour_time*10 && valve_flag_1 == 1 ){
            servo_1.write(0);
            tmr=millis();
            valve_flag_1 = 0;
            servo_flag = 1;
          }
          caret(k);
        }
        //====Мятный сироп (10 мл.)====
        if (drinks[k]==2 && dist > dist_min && dist < dist_max && stepper_caret.ready() == true && (sum_flags == 0 || valve_flag_2 == 1)){
          //valve(servo_2, valve_flag_2, 1, pour_time*2);
          if (valve_flag_2 == 0 && dist > dist_min && dist < dist_max){
            servo_2.write(90);
            valve_flag_2 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_2 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_2.write(0);
            time_2 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==pour_time*2 && valve_flag_2 == 1 ){
            servo_2.write(0);
            tmr=millis();
            valve_flag_2 = 0;
            servo_flag = 1;
          }
          caret(k);
        }
        //====Апельсиновый сок (40 мл.)====
        if (drinks[k]==3 && dist > dist_min && dist < dist_max && stepper_caret.ready() == true && (sum_flags == 0 || valve_flag_3 == 1)){
          //valve(servo_3, valve_flag_3, 1, pour_time*8);
          if (valve_flag_3 == 0 && dist > dist_min && dist < dist_max){
            servo_3.write(90);
            valve_flag_2 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_3 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_3.write(0);
            time_3 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==time_3 && valve_flag_3 == 1 ){
            servo_3.write(0);
            tmr=millis();
            valve_flag_3 = 0;
            servo_flag = 1;
          }
          caret(k);
        }
        //====Лимонад “Мятный” (80 мл. газированной воды + 20 мл. мятного сиропа)====
        if (drinks[k]==4 && dist > dist_min && dist < dist_max && stepper_caret.ready() == true && (sum_flags == 0 || valve_flag_4 == 1)){ 
          //valve(servo_1, valve_flag_4, 0, pour_time*16);
          if (valve_flag_4 == 0 && dist > dist_min && dist < dist_max){
            servo_1.write(90);
            valve_flag_4 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_4 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_1.write(0);
            time_4 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==time_4 && valve_flag_3 == 1 ){
            servo_1.write(0);
            tmr=millis();
            valve_flag_4 = 0;
            servo_flag = 0;
          }
          //valve(servo_2, valve_flag_4, 1, pour_time*4);
          if (valve_flag_4 == 0 && dist > dist_min && dist < dist_max){
            servo_2.write(90);
            valve_flag_4 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_4 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_2.write(0);
            time_5 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==time_5 && valve_flag_4 == 1 ){
            servo_2.write(0);
            tmr=millis();
            valve_flag_4 = 0;
            servo_flag = 1;
          }
          caret(k);
        }
        //====Лимонад “Заводной апельсин” (30 мл. газированной воды + 50 мл. апельсинового сока)====
        if (drinks[k]==5 && dist > dist_min && dist < dist_max && stepper_caret.ready() == true && (sum_flags == 0 || valve_flag_5 == 1)){
          //valve(servo_1, valve_flag_5, 0, pour_time*6);
          if (valve_flag_5 == 0 && dist > dist_min && dist < dist_max){
            servo_1.write(90);
            valve_flag_5 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_5 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_1.write(0);
            time_6 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==time_6 && valve_flag_5 == 1 ){
            servo_1.write(0);
            tmr=millis();
            valve_flag_5 = 0;
            servo_flag = 0;
          }
          //valve(servo_3, valve_flag_5, 1, pour_time*10);
          if (valve_flag_5 == 0 && dist > dist_min && dist < dist_max){
            servo_3.write(90);
            valve_flag_5 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_5 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_3.write(0);
            time_7 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==time_6 && valve_flag_5 == 1 ){
            servo_3.write(0);
            tmr=millis();
            valve_flag_5 = 0;
            servo_flag = 1;
          }
          caret(k);
        }
        //====Лимонад ‘Тройной” (35 мл. газированной воды + 45 мл. апельсинового сока + 10 мл. мятного сиропа)====
        if (drinks[k]==6 && dist > dist_min && dist < dist_max && stepper_caret.ready() == true && (sum_flags == 0 || valve_flag_6 == 1)){
          //valve(servo_1, valve_flag_6, 0, pour_time*7);
          if (valve_flag_5 == 0 && dist > dist_min && dist < dist_max){
            servo_1.write(90);
            valve_flag_6 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_6 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_1.write(0);
            time_8 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==time_6 && valve_flag_6 == 1 ){
            servo_1.write(0);
            tmr=millis();
            valve_flag_6 = 0;
            servo_flag = 0;
          }
          //valve(servo_2, valve_flag_6, 0, pour_time*9);
          if (valve_flag_6 == 0 && dist > dist_min && dist < dist_max){
            servo_2.write(90);
            valve_flag_5 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_6 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_2.write(0);
            time_9 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==time_6 && valve_flag_6 == 1 ){
            servo_2.write(0);
            tmr=millis();
            valve_flag_6 = 0;
            servo_flag = 0;
          }
          //valve(servo_3, valve_flag_6, 1, pour_time*2);
          if (valve_flag_6 == 0 && dist > dist_min && dist < dist_max){
            servo_3.write(90);
            valve_flag_5 = 1;
            FLAG = 0;
          }
          //экстренное закрытие
          if (valve_flag_6 == 1 && (dist < dist_min || dist > dist_max) && FLAG == 0){
            servo_3.write(0);
            time_10 -= (millis() - tmr);
            FLAG = 1;
            tmr == millis();
          }
          //закрыть клапан
          if (millis()-tmr==time_6 && valve_flag_6 == 1 ){
            servo_3.write(0);
            tmr=millis();
            valve_flag_6 = 0;
            servo_flag = 1;
          }
          caret(k);
        }
      }
  }  
  // ======= конвейер =======!!!!!
  if (caret_flag==1 && stepper_caret.ready() == true){
    stepper_belt.setTarget(h);
    if (stepper_belt.ready() && dist < dist_max && count>0){
      stepper_belt.setTarget(stepper_belt.getCurrent() + next);
      count-=1;
    }
    if (count == 0){
      stepper_belt.reset();
    }
  }
}
//ф-ция движения каретки
void caret(int k) {
  if (servo_flag==1){
    if (k==3){
      stepper_caret.setTarget(h); //вернуться к первому стакану
      caret_flag == 1;
    }
    else{
      if (drinks[k+1]!=0){
        stepper_caret.setTarget(stepper_caret.getCurrent() + next); //доехать до следущего стакана 
      }
      else {
        stepper_caret.setTarget(h); //вернуться к первому стакану
        caret_flag == 1;
      }
    }
  }
}
