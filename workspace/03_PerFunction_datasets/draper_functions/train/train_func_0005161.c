adt7316_i2c_multi_read(void *client, u8 reg, u8 count, u8 *data)
{
	struct i2c_client *cl = client;
	int i, ret = 0;

	if (count > ADT7316_REG_MAX_ADDR)
		count = ADT7316_REG_MAX_ADDR;

	for (i = 0; i < count; i++) {
		ret = adt7316_i2c_read(cl, reg, &data[i]);
		if (ret < 0) {
			dev_err(&cl->dev, "I2C multi read error\n");
			return ret;
		}
	}

	return 0;
}
