isl29003_get_adc_value(struct i2c_client *client)
{
	struct isl29003_data *data = i2c_get_clientdata(client);
	int lsb, msb, range, bitdepth;

	mutex_lock(&data->lock);
	lsb = i2c_smbus_read_byte_data(client, ISL29003_REG_LSB_SENSOR);

	if (lsb < 0) {
		mutex_unlock(&data->lock);
		return lsb;
	}

	msb = i2c_smbus_read_byte_data(client, ISL29003_REG_MSB_SENSOR);
	mutex_unlock(&data->lock);

	if (msb < 0)
		return msb;

	range = isl29003_get_range(client);
	bitdepth = (4 - isl29003_get_resolution(client)) * 4;
	return (((msb << 8) | lsb) * gain_range[range]) >> bitdepth;
}
