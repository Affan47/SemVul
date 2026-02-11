stv0900_read_reg(struct stv0900_internal *intp, u16 reg)
{
	int ret;
	u8 b0[] = { MSB(reg), LSB(reg) };
	u8 buf = 0;
	struct i2c_msg msg[] = {
		{
			.addr	= intp->i2c_addr,
			.flags	= 0,
			.buf = b0,
			.len = 2,
		}, {
			.addr	= intp->i2c_addr,
			.flags	= I2C_M_RD,
			.buf = &buf,
			.len = 1,
		},
	};

	ret = i2c_transfer(intp->i2c_adap, msg, 2);
	if (ret != 2)
		dprintk("%s: i2c error %d, reg[0x%02x]\n",
				__func__, ret, reg);

	return buf;
}
