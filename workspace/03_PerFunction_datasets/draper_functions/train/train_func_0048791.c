lock_tuner(struct tda10021_state* state)
{
	u8 buf[2] = { 0x0f, tda10021_inittab[0x0f] | 0x80 };
	struct i2c_msg msg = {.addr=state->config->demod_address, .flags=0, .buf=buf, .len=2};

	if(i2c_transfer(state->i2c, &msg, 1) != 1)
	{
		printk("tda10021: lock tuner fails\n");
		return -EREMOTEIO;
	}
	return 0;
}
