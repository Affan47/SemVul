EyeboxOne_use_led(int fd, int led, int color)
{
	char buffer[16];
	int a,b;

	if(led > 3 || led < 1)
		return;

	switch(color){
		case LED_OFF:
			a=b=0;
			break;
		case LED_RED:
			a=1;
			b=0;
			break;
		case LED_ORANGE:
			a=1;
			b=1;
			break;
		case LED_GREEN:
			a=0;
			b=1;
			break;
		default:
			a=b=0;
	}

	sprintf(buffer, "\E[%d;%dL",led+(led-1),a);
	write(fd,buffer,strlen(buffer));
	sprintf(buffer, "\E[%d;%dL",led+(led-1)+1,b);
	write(fd,buffer,strlen(buffer));

}
