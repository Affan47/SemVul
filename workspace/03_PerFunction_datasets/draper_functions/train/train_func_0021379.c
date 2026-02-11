slopes_to_scale(const struct slope *slopes, u8 num, s16 val)
{
	u8 i;
	u16 rest;
	u16 ret = 0;
	for (i = 0; i < num; i++) {
		if (val > slopes[i].range)
			rest = slopes[i].range;
		else
			rest = val;
		ret += (rest * slopes[i].slope) / slopes[i].range;
		val -= rest;
	}
	return ret;
}
