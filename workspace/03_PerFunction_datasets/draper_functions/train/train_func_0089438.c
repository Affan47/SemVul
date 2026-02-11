tda18218_wr_regs(struct tda18218_priv *priv, u8 reg, u8 *val, u8 len)
{
	int ret = 0, len2, remaining;
	u8 buf[MAX_XFER_SIZE];
	struct i2c_msg msg[1] = {
		{
			.addr = priv->cfg->i2c_address,
			.flags = 0,
			.buf = buf,
		}
	};

	if (1 + len > sizeof(buf)) {
		dev_warn(&priv->i2c->dev,
			 "%s: i2c wr reg=%04x: len=%d is too big!\n",
			 KBUILD_MODNAME, reg, len);
		return -EINVAL;
	}

	for (remaining = len; remaining > 0;
			remaining -= (priv->cfg->i2c_wr_max - 1)) {
		len2 = remaining;
		if (len2 > (priv->cfg->i2c_wr_max - 1))
			len2 = (priv->cfg->i2c_wr_max - 1);

		msg[0].len = 1 + len2;
		buf[0] = reg + len - remaining;
		memcpy(&buf[1], &val[len - remaining], len2);

		ret = i2c_transfer(priv->i2c, msg, 1);
		if (ret != 1)
			break;
	}

	if (ret == 1) {
		ret = 0;
	} else {
		dev_warn(&priv->i2c->dev, "%s: i2c wr failed=%d reg=%02x " \
				"len=%d\n", KBUILD_MODNAME, ret, reg, len);
		ret = -EREMOTEIO;
	}

	return ret;
}
