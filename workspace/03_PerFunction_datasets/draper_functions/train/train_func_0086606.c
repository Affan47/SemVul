i2c_readbytes(struct nxt200x_state *state, u8 addr, u8 *buf, u8 len)
{
	int err;
	struct i2c_msg msg = { .addr = addr, .flags = I2C_M_RD, .buf = buf, .len = len };

	if ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) {
		pr_warn("%s: i2c read error (addr 0x%02x, err == %i)\n",
			__func__, addr, err);
		return -EREMOTEIO;
	}
	return 0;
}
