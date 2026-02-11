max8925_write_device(struct i2c_client *i2c,
				       int reg, int bytes, void *src)
{
	unsigned char buf[9];
	int ret;

	buf[0] = (unsigned char)reg;
	memcpy(&buf[1], src, bytes);

	ret = i2c_master_send(i2c, buf, bytes + 1);
	if (ret < 0)
		return ret;
	return 0;
}
