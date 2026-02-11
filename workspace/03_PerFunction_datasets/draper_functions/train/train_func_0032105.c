FAN_TO_REG(long rpm, int div)
{
	long rpmdiv;
	if (rpm == 0)
		return 0;
	rpmdiv = clamp_val(rpm, 1, 960000) * div;
	return clamp_val((480000 + rpmdiv / 2) / rpmdiv, 1, 255);
}
