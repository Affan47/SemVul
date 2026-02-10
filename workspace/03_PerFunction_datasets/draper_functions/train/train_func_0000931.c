smi_read_eeprom(struct i2c_adapter *i2c, u16 reg, u8 *data, u16 size)
{
	int ret;
	u8 b0[2] = { (reg >> 8) & 0xff, reg & 0xff };

	struct i2c_msg msg[] = {
		{ .addr = 0x50, .flags = 0,
			.buf = b0, .len = 2 },
		{ .addr = 0x50, .flags = I2C_M_RD,
			.buf = data, .len = size }
	};

	ret = i2c_transfer(i2c, msg, 2);

	if (ret != 2) {
		dev_err(&i2c->dev, "%s: reg=0x%x (error=%d)\n",
			__func__, reg, ret);
		return ret;
	}
	return ret;
}
