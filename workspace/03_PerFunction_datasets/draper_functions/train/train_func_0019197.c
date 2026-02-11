GMT_rd_from_gymd (GMT_LONG gy, GMT_LONG gm, GMT_LONG gd) {


	double s;
	GMT_LONG	day_offset, yearm1, rd;


	if (gm <= 2) {
		day_offset = 0;
	}
	else {
		if ( GMT_is_gleap (gy) ) {
			day_offset = -1;
		}
		else {
			day_offset = -2;
		}
	}

	yearm1 = gy - 1;
	rd = day_offset + gd + 365 * yearm1;
	s = floor(yearm1/4.0) - floor(yearm1/100.0) + floor(yearm1/400.0);
	s += floor( (367 * gm - 362)/12.0);
	rd += (GMT_LONG)irint(s);
	return ((GMT_cal_rd)rd);
}
