octeon_i2c_init_lowlevel(struct octeon_i2c *i2c)
{
	u8 status = 0;
	int tries;


	octeon_i2c_reg_write(i2c, SW_TWSI_EOP_TWSI_RST, 0);

	for (tries = 10; tries && status != STAT_IDLE; tries--) {
		udelay(1);
		status = octeon_i2c_stat_read(i2c);
		if (status == STAT_IDLE)
			break;
	}

	if (status != STAT_IDLE) {
		dev_err(i2c->dev, "%s: TWSI_RST failed! (0x%x)\n",
			__func__, status);
		return -EIO;
	}


	octeon_i2c_hlc_enable(i2c);
	octeon_i2c_hlc_disable(i2c);
	return 0;
}
