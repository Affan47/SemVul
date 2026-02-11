hdcs_reg_write_seq(struct sd *sd, u8 reg, u8 *vals, u8 len)
{
	u8 regs[I2C_MAX_BYTES * 2];
	int i;

	if (unlikely((len <= 0) || (len >= I2C_MAX_BYTES) ||
		     (reg + len > 0xff)))
		return -EINVAL;

	for (i = 0; i < len; i++) {
		regs[2 * i] = reg;
		regs[2 * i + 1] = vals[i];


		reg += 2;
	}

	return stv06xx_write_sensor_bytes(sd, regs, len);
}
