cx22702_writereg(struct cx22702_state *state, u8 reg, u8 data)
{
	int ret;
	u8 buf[] = { reg, data };
	struct i2c_msg msg = {
		.addr = state->config->demod_address, .flags = 0,
			.buf = buf, .len = 2 };

	ret = i2c_transfer(state->i2c, &msg, 1);

	if (unlikely(ret != 1)) {
		printk(KERN_ERR
			"%s: error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			__func__, reg, data, ret);
		return -1;
	}

	return 0;
}
