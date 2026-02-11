i2c_av_read(struct i2c_adapter *i2c, u16 reg)
{
	int ret;
	u8 buf[2];
	struct i2c_msg msg = {
		.addr	= 0x88 >> 1,
		.flags	= 0,
		.buf	= buf,
		.len	= 2
	};

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	ret = i2c_transfer(i2c, &msg, 1);

	if (ret != 1)
		printk(KERN_ERR "%s: i2c write error!\n", __func__);

	msg.flags = I2C_M_RD;
	msg.len = 1;

	ret = i2c_transfer(i2c, &msg, 1);

	if (ret != 1)
		printk(KERN_ERR "%s: i2c read error!\n", __func__);

	return buf[0];
}
