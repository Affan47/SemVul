m88rs2000_writereg(struct m88rs2000_state *state,
	u8 reg, u8 data)
{
	int ret;
	u8 buf[] = { reg, data };
	struct i2c_msg msg = {
		.addr = state->config->demod_addr,
		.flags = 0,
		.buf = buf,
		.len = 2
	};

	ret = i2c_transfer(state->i2c, &msg, 1);

	if (ret != 1)
		deb_info("%s: writereg error (reg == 0x%02x, val == 0x%02x, "
			"ret == %i)\n", __func__, reg, data, ret);

	return (ret != 1) ? -EREMOTEIO : 0;
}
