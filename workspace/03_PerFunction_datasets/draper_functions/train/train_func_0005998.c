octeon_i2c_hlc_write(struct octeon_i2c *i2c, struct i2c_msg *msgs)
{
	int i, j, ret = 0;
	u64 cmd;

	octeon_i2c_hlc_enable(i2c);
	octeon_i2c_hlc_int_clear(i2c);

	cmd = SW_TWSI_V | SW_TWSI_SOVR;

	cmd |= (u64)(msgs[0].len - 1) << SW_TWSI_SIZE_SHIFT;

	cmd |= (u64)(msgs[0].addr & 0x7full) << SW_TWSI_ADDR_SHIFT;

	if (msgs[0].flags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10;
	else
		cmd |= SW_TWSI_OP_7;

	for (i = 0, j = msgs[0].len - 1; i  < msgs[0].len && i < 4; i++, j--)
		cmd |= (u64)msgs[0].buf[j] << (8 * i);

	if (msgs[0].len > 4) {
		u64 ext = 0;

		for (i = 0; i < msgs[0].len - 4 && i < 4; i++, j--)
			ext |= (u64)msgs[0].buf[j] << (8 * i);
		octeon_i2c_writeq_flush(ext, i2c->twsi_base + SW_TWSI_EXT(i2c));
	}

	octeon_i2c_writeq_flush(cmd, i2c->twsi_base + SW_TWSI(i2c));
	ret = octeon_i2c_hlc_wait(i2c);
	if (ret)
		goto err;

	cmd = __raw_readq(i2c->twsi_base + SW_TWSI(i2c));
	if ((cmd & SW_TWSI_R) == 0)
		return octeon_i2c_check_status(i2c, false);

err:
	return ret;
}
