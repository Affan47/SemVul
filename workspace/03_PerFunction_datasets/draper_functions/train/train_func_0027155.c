ov965x_set_white_balance(struct ov965x *ov965x, int awb)
{
	int ret;
	u8 reg;

	ret = ov965x_read(ov965x->client, REG_COM8, &reg);
	if (!ret) {
		reg = awb ? reg | REG_COM8 : reg & ~REG_COM8;
		ret = ov965x_write(ov965x->client, REG_COM8, reg);
	}
	if (!ret && !awb) {
		ret = ov965x_write(ov965x->client, REG_BLUE,
				   ov965x->ctrls.blue_balance->val);
		if (ret < 0)
			return ret;
		ret = ov965x_write(ov965x->client, REG_RED,
				   ov965x->ctrls.red_balance->val);
	}
	return ret;
}
