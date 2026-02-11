calc_pitch_shift_trad(int cents)
{
	int val;
	val = (cents * 0x80) / 1200;
	if (val < -128) val = -128;
	if (val > 127) val = 127;
	if (val < 0)
		return 0x100 + val;
	else
		return val;
}
