i2c_lpc2k_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			  int msg_num)
{
	struct lpc2k_i2c *i2c = i2c_get_adapdata(adap);
	int ret, i;
	u32 stat;


	stat = readl(i2c->base + LPC24XX_I2STAT);
	if (stat != M_I2C_IDLE) {

		return i2c_lpc2k_clear_arb(i2c);
	}


	for (i = 0; i < msg_num; i++) {

		i2c->msg = &msgs[i];
		i2c->msg_idx = 0;
		i2c->msg_status = -EBUSY;
		i2c->is_last = (i == (msg_num - 1));

		ret = lpc2k_process_msg(i2c, i);
		if (ret)
			return ret;
	}

	return msg_num;
}
