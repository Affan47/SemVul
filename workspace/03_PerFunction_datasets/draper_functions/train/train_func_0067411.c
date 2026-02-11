i2c_read(struct i2c_adapter *adap,
		    u8 adr, u8 *msg, int len, u8 *answ, int alen)
{
	struct i2c_msg msgs[2] = {
		{
			.addr = adr, .flags = 0,
			.buf = msg, .len = len
		}, {
			.addr = adr, .flags = I2C_M_RD,
			.buf = answ, .len = alen
		}
	};
	if (i2c_transfer(adap, msgs, 2) != 2)
		return -1;
	return 0;
}
