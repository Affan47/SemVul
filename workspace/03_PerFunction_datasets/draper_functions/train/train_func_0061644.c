sp8870_writereg (struct sp8870_state* state, u16 reg, u16 data)
{
	u8 buf [] = { reg >> 8, reg & 0xff, data >> 8, data & 0xff };
	struct i2c_msg msg = { .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 4 };
	int err;

	if ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) {
		dprintk ("%s: writereg error (err == %i, reg == 0x%02x, data == 0x%02x)\n", __func__, err, reg, data);
		return -EREMOTEIO;
	}

	return 0;
}
