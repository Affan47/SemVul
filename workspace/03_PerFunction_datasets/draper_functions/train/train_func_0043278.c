pwm_mode(const struct it87_data *data, int nr)
{
	int ctrl = data->fan_main_ctrl & (1 << nr);

	if (ctrl == 0 && data->type != it8603)
		return 0;
	if (data->pwm_ctrl[nr] & 0x80)
		return 2;
	else
		return 1;
}
