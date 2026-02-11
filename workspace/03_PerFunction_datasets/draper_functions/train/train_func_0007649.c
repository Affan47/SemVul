rs5c_oscillator_setup(struct rs5c372 *rs5c372)
{
	unsigned char buf[2];
	int addr, i, ret = 0;

	if (rs5c372->type == rtc_r2025sd) {
		if (!(rs5c372->regs[RS5C_REG_CTRL2] & R2025_CTRL2_XST))
			return ret;
		rs5c372->regs[RS5C_REG_CTRL2] &= ~R2025_CTRL2_XST;
	} else {
		if (!(rs5c372->regs[RS5C_REG_CTRL2] & RS5C_CTRL2_XSTP))
			return ret;
		rs5c372->regs[RS5C_REG_CTRL2] &= ~RS5C_CTRL2_XSTP;
	}

	addr   = RS5C_ADDR(RS5C_REG_CTRL1);
	buf[0] = rs5c372->regs[RS5C_REG_CTRL1];
	buf[1] = rs5c372->regs[RS5C_REG_CTRL2];


	switch (rs5c372->type) {
	case rtc_rs5c372a:
	case rtc_rs5c372b:
		buf[1] |= RS5C372_CTRL2_24;
		rs5c372->time24 = 1;
		break;
	case rtc_r2025sd:
	case rtc_r2221tl:
	case rtc_rv5c386:
	case rtc_rv5c387a:
		buf[0] |= RV5C387_CTRL1_24;
		rs5c372->time24 = 1;
		break;
	default:

		break;
	}

	for (i = 0; i < sizeof(buf); i++) {
		addr = RS5C_ADDR(RS5C_REG_CTRL1 + i);
		ret = i2c_smbus_write_byte_data(rs5c372->client, addr, buf[i]);
		if (unlikely(ret < 0))
			return ret;
	}

	rs5c372->regs[RS5C_REG_CTRL1] = buf[0];
	rs5c372->regs[RS5C_REG_CTRL2] = buf[1];

	return 0;
}
