const byte trig_pin = 12;
const byte echo_pin = 14;
float sound_speed = 0.034;
int buzzerPin = 26;
int buzzer_interval = 0;

//  array of led_pins
byte led_pins[] = {13, 15, 2, 4, 5, 18, 19, 21, 22, 23};

void setup(){
  //  defining nature of sensor pins
  pinMode(trig_pin , OUTPUT);
  pinMode(echo_pin , INPUT);
  pinMode(buzzerPin, OUTPUT);
  //  declaring all led pins as output
  for (int i = 0; i < sizeof(led_pins); i++){
    pinMode(led_pins[i] , OUTPUT);
  }
  Serial.begin(115200);
  indicator_testing();
}

void loop(){
  int distance = get_distance();
  indicator(distance);
  //  so that simulator works better
  delay(10);
}

void indicator_testing(){
  //  turning all leds on
  for (int i = 0; i < sizeof(led_pins); i++){
    digitalWrite(led_pins[i] , HIGH);
    delay(70);
  }
  //  all leds off
  for (int i = sizeof(led_pins) - 1; i >= 0; i--){
    digitalWrite(led_pins[i] , LOW);
    delay(70);
  }
}

int get_distance(){

  //  getting ready before sending tigger burst
  digitalWrite(trig_pin , LOW);
  delayMicroseconds(2);

  //  sending trigger burst
  digitalWrite(trig_pin , HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin , LOW);

  //  waiting for response : checking HIGH duration of echo pin
  long int duration = pulseIn(echo_pin , HIGH);
  long int distance = (duration * sound_speed) / 2;

  return distance;

}

void indicator(int distance){

  if (distance  <=  150  &&  distance  >  135)led_on(1);
  else if (distance  <=  135  &&  distance  >  120)led_on(2);
  else if (distance  <=  120  &&  distance  >  105)led_on(3);
  else if (distance  <=  105  &&  distance  >  90)led_on(4);
  else if (distance  <=  90  &&  distance  >  75)led_on(5);
  else if (distance  <=  75  &&  distance  >  60)led_on(6);
  else if (distance  <=  60  &&  distance  >  45)led_on(7);
  else if (distance  <=  45  &&  distance  >  30)led_on(8);
  else if (distance  <=  30  &&  distance  >  15)led_on(9);
  else if (distance  <=  15  &&  distance  >  0)led_on(10);
  else led_on(0);

  if(distance <= 150){
    //  calculating buzzer interval, mapping with distance
    buzzer_interval = map(distance , 0 , 150 , 0 , 1000);
    buzzer();
    delay(buzzer_interval);
  }
}

void led_on(byte led_count){
  //  total led which are going to be on
  for (int i = 0; i < led_count; i++){
    digitalWrite(led_pins[i] , HIGH);
  }

  //  total leds which are going to be off
  for (int i = led_count; i < sizeof(led_pins); i++){
    digitalWrite(led_pins[i] , LOW);
  }
}

void buzzer(){
  for (int j = 0; j < 3; j++)
    { 
      digitalWrite(buzzerPin, HIGH);
      delay(2);
      digitalWrite(buzzerPin, LOW);
      delay(2);
    }
}