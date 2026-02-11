jalali_get_jyear_info(struct jyinfo* year)
{
	int y = year->y;
	year->lf = jalali_is_jleap(year->y);
	int i;
	int d = (year->y >= JALALI_LEAP_BASE) ? 1 : -1;
	int c = 0;

	for (i=JALALI_LEAP_BASE; ; i+=d) {
		if (jalali_is_jleap(i)) {
			c++;
		}

		if (i == year->y)
			break;
	}

	year->apl = c * d;
	year->pl = (d > 0) ? c % JALALI_TOTAL_LEAPS_IN_PERIOD :
		JALALI_TOTAL_LEAPS_IN_PERIOD - (c % JALALI_TOTAL_LEAPS_IN_PERIOD);
	year->rl = JALALI_TOTAL_LEAPS_IN_PERIOD - year->pl;

	y-= JALALI_LEAP_BASE;
	y%= JALALI_LEAP_PERIOD;
	if (y < 0)
		y+= JALALI_LEAP_PERIOD;

	year->p = y;
	year->r = JALALI_LEAP_PERIOD - y - 1;

	return ;
}
