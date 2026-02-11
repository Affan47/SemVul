apds9300_get_adc_val(struct apds9300_data *data, int adc_number)
{
	int ret;
	u8 flags = APDS9300_CMD | APDS9300_WORD;

	if (!data->power_state)
		return -EBUSY;


	flags |= adc_number ? APDS9300_DATA1LOW : APDS9300_DATA0LOW;

	ret = i2c_smbus_read_word_data(data->client, flags);
	if (ret < 0)
		dev_err(&data->client->dev,
			"failed to read ADC%d value\n", adc_number);

	return ret;
}
