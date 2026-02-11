bq2415x_i2c_read(struct bq2415x_device *bq, u8 reg)
{
	struct i2c_client *client = to_i2c_client(bq->dev);
	struct i2c_msg msg[2];
	u8 val;
	int ret;

	if (!client->adapter)
		return -ENODEV;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].buf = &reg;
	msg[0].len = sizeof(reg);
	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = &val;
	msg[1].len = sizeof(val);

	mutex_lock(&bq2415x_i2c_mutex);
	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	mutex_unlock(&bq2415x_i2c_mutex);

	if (ret < 0)
		return ret;

	return val;
}
