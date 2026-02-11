tps6507x_i2c_write_device(struct tps6507x_dev *tps6507x, char reg,
				   int bytes, void *src)
{
	struct i2c_client *i2c = tps6507x->i2c_client;

	u8 msg[TPS6507X_MAX_REGISTER + 1];
	int ret;

	if (bytes > TPS6507X_MAX_REGISTER)
		return -EINVAL;

	msg[0] = reg;
	memcpy(&msg[1], src, bytes);

	ret = i2c_master_send(i2c, msg, bytes + 1);
	if (ret < 0)
		return ret;
	if (ret != bytes + 1)
		return -EIO;
	return 0;
}
