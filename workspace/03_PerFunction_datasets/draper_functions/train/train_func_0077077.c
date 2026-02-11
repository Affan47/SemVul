af9013_wr_regs_i2c(struct af9013_state *priv, u8 mbox, u16 reg,
	const u8 *val, int len)
{
	int ret;
	u8 buf[MAX_XFER_SIZE];
	struct i2c_msg msg[1] = {
		{
			.addr = priv->config.i2c_addr,
			.flags = 0,
			.len = 3 + len,
			.buf = buf,
		}
	};

	if (3 + len > sizeof(buf)) {
		dev_warn(&priv->i2c->dev,
			 "%s: i2c wr reg=%04x: len=%d is too big!\n",
			 KBUILD_MODNAME, reg, len);
		return -EINVAL;
	}

	buf[0] = (reg >> 8) & 0xff;
	buf[1] = (reg >> 0) & 0xff;
	buf[2] = mbox;
	memcpy(&buf[3], val, len);

	ret = i2c_transfer(priv->i2c, msg, 1);
	if (ret == 1) {
		ret = 0;
	} else {
		dev_warn(&priv->i2c->dev, "%s: i2c wr failed=%d reg=%04x " \
				"len=%d\n", KBUILD_MODNAME, ret, reg, len);
		ret = -EREMOTEIO;
	}
	return ret;
}
