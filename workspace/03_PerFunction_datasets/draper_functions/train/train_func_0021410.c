us5182d_set_opmode(struct us5182d_data *data, u8 mode)
{
	int ret;

	ret = i2c_smbus_read_byte_data(data->client, US5182D_REG_CFG0);
	if (ret < 0)
		return ret;


	ret = ret | US5182D_CFG0_ONESHOT_EN;


	ret = ret & ~US5182D_OPMODE_MASK;
	ret = ret | (mode << US5182D_OPMODE_SHIFT);


	ret = i2c_smbus_write_byte_data(data->client, US5182D_REG_CFG0, ret);
	if (ret < 0)
		return ret;

	if (mode == data->opmode)
		return 0;

	ret = i2c_smbus_write_byte_data(data->client, US5182D_REG_MODE_STORE,
					US5182D_STORE_MODE);
	if (ret < 0)
		return ret;

	data->opmode = mode;
	msleep(US5182D_OPSTORE_SLEEP_TIME);

	return 0;
}
