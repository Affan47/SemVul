adau1701_reg_write(void *context, unsigned int reg,
			      unsigned int value)
{
	struct i2c_client *client = context;
	unsigned int i;
	unsigned int size;
	uint8_t buf[5];
	int ret;

	size = adau1701_register_size(&client->dev, reg);
	if (size == 0)
		return -EINVAL;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	for (i = size + 1; i >= 2; --i) {
		buf[i] = value;
		value >>= 8;
	}

	ret = i2c_master_send(client, buf, size + 2);
	if (ret == size + 2)
		return 0;
	else if (ret < 0)
		return ret;
	else
		return -EIO;
}
