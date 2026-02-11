adt7316_i2c_write(void *client, u8 reg, u8 data)
{
	struct i2c_client *cl = client;
	int ret = 0;

	ret = i2c_smbus_write_byte_data(cl, reg, data);
	if (ret < 0)
		dev_err(&cl->dev, "I2C write error\n");

	return ret;
}
