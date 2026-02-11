awe_calc_pan(int val)
{
	if (val < -500) return 0;
	else if (val > 500) val = 127;
	return (char)((val + 500) * 127 / 1000);
}
