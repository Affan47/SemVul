cvt_auto_temp(int input)
{
	if (input == ADT7470_PWM_ALL_TEMPS)
		return 0;
	if (input < 1 || !is_power_of_2(input))
		return -EINVAL;
	return ilog2(input) + 1;
}
