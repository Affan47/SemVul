mt2131_writereg(struct mt2131_priv *priv, u8 reg, u8 val)
{
	u8 buf[2] = { reg, val };
	struct i2c_msg msg = { .addr = priv->cfg->i2c_address, .flags = 0,
			       .buf = buf, .len = 2 };

	if (i2c_transfer(priv->i2c, &msg, 1) != 1) {
		printk(KERN_WARNING "mt2131 I2C write failed\n");
		return -EREMOTEIO;
	}
	return 0;
}
