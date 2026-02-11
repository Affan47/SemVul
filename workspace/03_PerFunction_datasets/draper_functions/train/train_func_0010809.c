nxt6000_readreg(struct nxt6000_state* state, u8 reg)
{
	int ret;
	u8 b0[] = { reg };
	u8 b1[] = { 0 };
	struct i2c_msg msgs[] = {
		{.addr = state->config->demod_address,.flags = 0,.buf = b0,.len = 1},
		{.addr = state->config->demod_address,.flags = I2C_M_RD,.buf = b1,.len = 1}
	};

	ret = i2c_transfer(state->i2c, msgs, 2);

	if (ret != 2)
		dprintk("nxt6000: nxt6000_read error (reg: 0x%02X, ret: %d)\n", reg, ret);

	return b1[0];
}
