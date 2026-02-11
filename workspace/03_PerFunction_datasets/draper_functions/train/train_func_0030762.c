mpu3050_hw_init(struct mpu3050_sensor *sensor)
{
	struct i2c_client *client = sensor->client;
	int ret;
	u8 reg;


	ret = i2c_smbus_write_byte_data(client, MPU3050_PWR_MGM,
					MPU3050_PWR_MGM_RESET);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_read_byte_data(client, MPU3050_PWR_MGM);
	if (ret < 0)
		return ret;

	ret &= ~MPU3050_PWR_MGM_CLKSEL;
	ret |= MPU3050_PWR_MGM_PLL_Z;
	ret = i2c_smbus_write_byte_data(client, MPU3050_PWR_MGM, ret);
	if (ret < 0)
		return ret;


	ret = i2c_smbus_write_byte_data(client, MPU3050_SMPLRT_DIV,
					MPU3050_DEFAULT_POLL_INTERVAL - 1);
	if (ret < 0)
		return ret;


	reg = MPU3050_DEFAULT_FS_RANGE;
	reg |= MPU3050_DLPF_CFG_42HZ << 3;
	reg |= MPU3050_EXT_SYNC_NONE << 5;
	ret = i2c_smbus_write_byte_data(client, MPU3050_DLPF_FS_SYNC, reg);
	if (ret < 0)
		return ret;

	return 0;
}
