__tsl2550_show_lux(struct i2c_client *client, char *buf)
{
	struct tsl2550_data *data = i2c_get_clientdata(client);
	u8 ch0, ch1;
	int ret;

	ret = tsl2550_get_adc_value(client, TSL2550_READ_ADC0);
	if (ret < 0)
		return ret;
	ch0 = ret;

	ret = tsl2550_get_adc_value(client, TSL2550_READ_ADC1);
	if (ret < 0)
		return ret;
	ch1 = ret;


	ret = tsl2550_calculate_lux(ch0, ch1);
	if (ret < 0)
		return ret;
	if (data->operating_mode == 1)
		ret *= 5;

	return sprintf(buf, "%d\n", ret);
}
