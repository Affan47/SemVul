itd1000_read_reg(struct itd1000_state *state, u8 reg)
{
	u8 val;
	struct i2c_msg msg[2] = {
		{ .addr = state->cfg->i2c_address, .flags = 0,        .buf = &reg, .len = 1 },
		{ .addr = state->cfg->i2c_address, .flags = I2C_M_RD, .buf = &val, .len = 1 },
	};


	itd1000_write_regs(state, (reg - 1) & 0xff, &state->shadow[(reg - 1) & 0xff], 1);

	if (i2c_transfer(state->i2c, msg, 2) != 2) {
		itd_warn("itd1000 I2C read failed\n");
		return -EREMOTEIO;
	}
	return val;
}
