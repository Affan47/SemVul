stk8312_set_sample_rate(struct stk8312_data *data, u8 rate)
{
	int ret;
	u8 masked_reg;
	u8 mode;
	struct i2c_client *client = data->client;

	if (rate == data->sample_rate_idx)
		return 0;

	mode = data->mode;

	ret = stk8312_set_mode(data, STK8312_MODE_STANDBY);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_read_byte_data(client, STK8312_REG_SR);
	if (ret < 0)
		goto err_activate;

	masked_reg = (ret & (~STK8312_SR_MASK)) | rate;

	ret = i2c_smbus_write_byte_data(client, STK8312_REG_SR, masked_reg);
	if (ret < 0)
		goto err_activate;

	data->sample_rate_idx = rate;

	return stk8312_set_mode(data, mode);

err_activate:
	dev_err(&client->dev, "failed to set sampling rate\n");
	stk8312_set_mode(data, mode);

	return ret;
}
