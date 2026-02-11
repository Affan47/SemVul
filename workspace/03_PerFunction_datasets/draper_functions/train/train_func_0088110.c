stk1160_i2c_read_reg(struct stk1160 *dev, u8 addr,
		u8 reg, u8 *value)
{
	int rc;


	rc = stk1160_write_reg(dev, STK1160_SICTL_SDA, addr);
	if (rc < 0)
		return rc;


	rc = stk1160_write_reg(dev, STK1160_SBUSR_RA, reg);
	if (rc < 0)
		return rc;


	rc = stk1160_write_reg(dev, STK1160_SICTL, 0x20);
	if (rc < 0)
		return rc;

	rc = stk1160_i2c_busy_wait(dev, 0x01);
	if (rc < 0)
		return rc;

	rc = stk1160_read_reg(dev, STK1160_SBUSR_RD, value);
	if (rc < 0)
		return rc;

	return 0;
}
