or51132_writebuf(struct or51132_state *state, const u8 *buf, int len)
{
	int err;
	struct i2c_msg msg = { .addr = state->config->demod_address,
			       .flags = 0, .buf = (u8*)buf, .len = len };


	if ((err = i2c_transfer(state->i2c, &msg, 1)) != 1) {
		printk(KERN_WARNING "or51132: I2C write (addr 0x%02x len %d) error: %d\n",
		       msg.addr, msg.len, err);
		return -EREMOTEIO;
	}
	return 0;
}
