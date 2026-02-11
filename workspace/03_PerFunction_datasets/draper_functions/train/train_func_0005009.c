automove (int j)
{

	char kindx,kindy;
	int speedx = 0;
	int speedy = 0;


	if (spr[j].mx != 0)
	{
		if (spr[j].mx < 0)
			kindx = '-'; else kindx = '+';
		if (kindx == '-') speedx = (spr[j].mx - (spr[j].mx * 2)); else
			speedx = spr[j].mx;
	} else kindx = '0';

	if (spr[j].my != 0)
	{
		if (spr[j].my < 0)
			kindy = '-'; else kindy = '+';
		if (kindy == '-') speedy = (spr[j].my - (spr[j].my * 2)); else
			speedy = spr[j].my;

	} else kindy = '0';

	int speed = speedx;
	if (speedy > speedx) speed = speedy;
	if (speed > 0)
		move(j,speed,kindx,kindy);


}
