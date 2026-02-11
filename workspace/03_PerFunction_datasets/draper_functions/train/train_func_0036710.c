ov7670_s_exp(struct v4l2_subdev *sd, int value)
{
	int ret;
	unsigned char com1, com8, aech, aechh;

	ret = ov7670_read(sd, REG_COM1, &com1) +
		ov7670_read(sd, REG_COM8, &com8) +
		ov7670_read(sd, REG_AECHH, &aechh);
	if (ret)
		return ret;

	com1 = (com1 & 0xfc) | (value & 0x03);
	aech = (value >> 2) & 0xff;
	aechh = (aechh & 0xc0) | ((value >> 10) & 0x3f);
	ret = ov7670_write(sd, REG_COM1, com1) +
		ov7670_write(sd, REG_AECH, aech) +
		ov7670_write(sd, REG_AECHH, aechh);

	if (ret == 0)
		ret = ov7670_write(sd, REG_COM8, com8 & ~COM8_AEC);
	return ret;
}
