nxt200x_writebytes (struct nxt200x_state* state, u8 reg,
			       const u8 *buf, u8 len)
{
	u8 buf2[MAX_XFER_SIZE];
	int err;
	struct i2c_msg msg = { .addr = state->config->demod_address, .flags = 0, .buf = buf2, .len = len + 1 };

	if (1 + len > sizeof(buf2)) {
		pr_warn("%s: i2c wr reg=%04x: len=%d is too big!\n",
			 __func__, reg, len);
		return -EINVAL;
	}

	buf2[0] = reg;
	memcpy(&buf2[1], buf, len);

	if ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) {
		pr_warn("%s: i2c write error (addr 0x%02x, err == %i)\n",
			__func__, state->config->demod_address, err);
		return -EREMOTEIO;
	}
	return 0;
}
