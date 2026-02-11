move_enemy_template_2(int quick, int maxspeed)
{
	h = -PIXEL2CS(diffy) / (1<<quick);
	v = PIXEL2CS(diffx) / (1<<quick);

	if(diffx > 0)
	{
		if(h > -maxspeed)
			h -= quick;
	}
	else if(diffx < 0)
	{
		if(h < maxspeed)
			h += quick;
	}
	if(diffy > 0)
	{
		if(v > -maxspeed)
			v -= quick;
	}
	else if(diffy < 0)
	{
		if(v < maxspeed)
			v += quick;
	}
	int ndi = speed2dir(h, v, 16);
	if(ndi > 0)
		di = ndi;
}
