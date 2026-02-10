adt7316_i2c_read(void *client, u8 reg, u8 *data)
{
	struct i2c_client *cl = client;
	int ret = 0;

	ret = i2c_smbus_write_byte(cl, reg);
	if (ret < 0) {
		dev_err(&cl->dev, "I2C fail to select reg\n");
		return ret;
	}

	ret = i2c_smbus_read_byte(client);
	if (ret < 0) {
		dev_err(&cl->dev, "I2C read error\n");
		return ret;
	}

	return 0;
}
