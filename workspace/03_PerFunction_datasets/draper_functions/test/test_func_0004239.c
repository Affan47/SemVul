TEMP_TO_REG(long val, s8 min, s8 max)
{
	return clamp_val((val + (val < 0 ? -500 : 500)) / 1000, min, max);
}
