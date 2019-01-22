// Visual Micro is in vMicro>General>Tutorial Mode
/*
	Name:       contest.ino
	Created:	2018/8/28 11:02:58
	Author:     WYMXEDQ
*/

int lotor1 = 10;//接IN1
int lotor2 = 11;//接IN2
int rotor1 = 9;//接IN3
int rotor2 = 8;//接IN4

int control1 = A0;//左侧（朝下）红外管
int control2 = A1;//左前方（朝下）红外管
int control3 = A2;//正前方（朝下）红外管
int control4 = A3;//正前方（朝前）红外管
int control5 = A4;//左侧（朝左）红外管
int control6 = A5;//左侧辅助红外管
int control7 = A6;//检测柱用红外管
int control8 = A7;//检测柱用红外管

boolean con1;//左侧（朝下）红外管信号
boolean con2;//左前方（朝下）红外管信号
boolean con3;//正前方（朝下）红外管信号
boolean con4;//正前方（朝前）红外管信号
boolean con5;//左侧（朝左）红外管信号
boolean con6;//左侧辅助红外管信号
boolean con7;//检测柱用红外管信号
boolean con8;//检测柱用红外管信号
//检测到时为低

boolean state = 0;
boolean state_con5 = 1;

int speed_dir = 175;//直走速度
int speed_rou = 100;//转弯速度
int speed_dir_barr = 175;//障碍物直走速度
int speed_rou_barr = 150;//障碍物转弯速度

void setup() {
	pinMode(lotor1, OUTPUT);
	pinMode(lotor2, OUTPUT);
	pinMode(rotor1, OUTPUT);         
	pinMode(rotor2, OUTPUT);//初始化控制电机引脚
	pinMode(control1, INPUT);
	pinMode(control2, INPUT);
	pinMode(control3, INPUT);
	pinMode(control4, INPUT);
	pinMode(control5, INPUT);
	pinMode(control6, INPUT);
	pinMode(control7, INPUT);
	pinMode(control8, INPUT);//初始化红外管
}

void loop() {
	con1 = digitalRead(control1);
	con2 = digitalRead(control2);
	con3 = digitalRead(control3);
	con4 = digitalRead(control4);
	con5 = digitalRead(control5);
	con6 = digitalRead(control6);
	con7 = digitalRead(control7);
	con8 = digitalRead(control8);//读取数码管信号
	if (state == 1) {
		if (con3 == 1) {
			state = 0;//跳出有障碍物时
		}
		if (con3 == 0) {
			if (state_con5 == 1) {
				if (con5 == 1) {
					lotor(speed_rou_barr, true);
					rotor(speed_rou_barr, false);//右拐
				}
				if (con5 == 0) {
					state_con5 = 0;
				}
			}
			if (state_con5 == 0) {
				if (con6 == 0) {
					lotor(speed_dir_barr, true);
					rotor(speed_dir_barr, true);//直走
				}
				if (con6 == 1) {
					lotor(speed_rou_barr, false);
					rotor(speed_rou_barr, true);//左拐
				}
			}
		}
	}//有障碍物
	if (state == 0) {
		if (con4 == 0 || con7 == 0 || con8 == 0) {
			state = 1;
			state_con5 = 1;//跳入有障碍物时
		}
		else {
			run_no();//无障碍物时
		}
	}//无障碍物
}
void run_no() {
	if (con3 == 0) {
		if (con1 == 1 && con2 == 0) {
			lotor(speed_dir, true);
			rotor(200, true);
		}//直走
		if (con1 == 0 && con2 == 0) {
			lotor(speed_rou_barr, false);
			rotor(speed_rou_barr, true);
		}//左拐
		if (con2 == 1) {
			lotor(speed_rou, true);
			rotor(speed_rou, false);
			_delay_ms(10);
		}//右拐
	}
	if (con3 == 1) {
		lotor(speed_rou, true);
		rotor(speed_rou, false);
		_delay_ms(300);
		lotor(speed_dir, true);
		rotor(speed_dir, true);
		_delay_ms(135);
	}//V字弯右拐
}//无障碍物时
void lotor(int speed, boolean direction) {
	if (direction) {
		analogWrite(lotor2, speed);
		digitalWrite(lotor1, LOW);
	}//正转
	if (direction) {
		analogWrite(lotor1, speed);
		digitalWrite(lotor2, LOW);
	}//倒转
}//左轮控制函数
void rotor(int speed, boolean direction) {
	if (direction) {
		analogWrite(rotor2, speed);
		digitalWrite(rotor1, LOW);
	}//正转
	if (direction) {
		analogWrite(rotor1, speed);
		digitalWrite(rotor2, LOW);
	}//倒转
}//右轮控制函数
