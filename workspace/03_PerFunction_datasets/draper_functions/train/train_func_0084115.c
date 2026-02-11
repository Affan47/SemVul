nxt6000_writereg(struct nxt6000_state* state, u8 reg, u8 data)
{
	u8 buf[] = { reg, data };
	struct i2c_msg msg = {.addr = state->config->demod_address,.flags = 0,.buf = buf,.len = 2 };
	int ret;

	if ((ret = i2c_transfer(state->i2c, &msg, 1)) != 1)
		dprintk("nxt6000: nxt6000_write error (reg: 0x%02X, data: 0x%02X, ret: %d)\n", reg, data, ret);

	return (ret != 1) ? -EIO : 0;
}
