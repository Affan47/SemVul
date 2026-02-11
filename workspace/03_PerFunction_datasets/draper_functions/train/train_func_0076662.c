stb0899_read_regs(struct stb0899_state *state, unsigned int reg, u8 *buf, u32 count)
{
	int status;

	u8 b0[] = { reg >> 8, reg & 0xff };

	struct i2c_msg msg[] = {
		{
			.addr	= state->config->demod_address,
			.flags	= 0,
			.buf	= b0,
			.len	= 2
		},{
			.addr	= state->config->demod_address,
			.flags	= I2C_M_RD,
			.buf	= buf,
			.len	= count
		}
	};

	status = i2c_transfer(state->i2c, msg, 2);
	if (status != 2) {
		if (status != -ERESTARTSYS)
			printk(KERN_ERR "%s Read error, Reg=[0x%04x], Count=%u, Status=%d\n",
			       __func__, reg, count, status);
		goto err;
	}


	if ((reg != 0xf2ff) && (reg != 0xf6ff) &&
	    (((reg & 0xff00) == 0xf200) || ((reg & 0xff00) == 0xf600)))
		_stb0899_read_reg(state, (reg | 0x00ff));

	if (unlikely(*state->verbose >= FE_DEBUGREG)) {
		int i;

		printk(KERN_DEBUG "%s [0x%04x]:", __func__, reg);
		for (i = 0; i < count; i++) {
			printk(" %02x", buf[i]);
		}
		printk("\n");
	}

	return 0;
err:
	return status < 0 ? status : -EREMOTEIO;
}
