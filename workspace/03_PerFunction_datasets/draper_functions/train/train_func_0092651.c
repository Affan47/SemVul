kGetAngle(state_t *s, int funct_nr, int argc, reg_t *argv)
{


	int x1 = SKPV(0);
	int y1 = SKPV(1);
	int x2 = SKPV(2);
	int y2 = SKPV(3);
	int xrel = x2 - x1;
	int yrel = y1 - y2;
	int angle;


	if (y1 < y2)
		yrel = -yrel;
	if (x2 < x1)
		xrel = -xrel;


	if (yrel == 0 && xrel == 0)
		angle = 0;
	else
		angle = 100 * xrel / (xrel + yrel);


	if (y1 < y2)
		angle = 200 - angle;
	if (x2 < x1)
		angle = 400 - angle;


	angle -= (angle + 9) / 10;

	return make_reg(0, angle);
}
