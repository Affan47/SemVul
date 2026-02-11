rtl8xxxu_init_mac(struct rtl8xxxu_priv *priv, struct rtl8xxxu_reg8val *array)
{
	int i, ret;
	u16 reg;
	u8 val;

	for (i = 0; ; i++) {
		reg = array[i].reg;
		val = array[i].val;

		if (reg == 0xffff && val == 0xff)
			break;

		ret = rtl8xxxu_write8(priv, reg, val);
		if (ret != 1) {
			dev_warn(&priv->udev->dev,
				 "Failed to initialize MAC\n");
			return -EAGAIN;
		}
	}

	rtl8xxxu_write8(priv, REG_MAX_AGGR_NUM, 0x0a);

	return 0;
}
