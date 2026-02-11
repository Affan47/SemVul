pwm_freq_to_reg(unsigned long val)
{
	if (val >= 187500)
		return 0x80;
	if (val >= 1475)
		return 0x80 | (48000000UL / (val << 8));
	if (val < 31)
		return 0x7f;
	else
		return 1000000UL / (val << 8);
}
