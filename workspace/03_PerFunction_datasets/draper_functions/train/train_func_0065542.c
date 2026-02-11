cxd2841er_sleep_tc_to_shutdown(struct cxd2841er_priv *priv)
{
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	if (priv->state != STATE_SLEEP_TC) {
		dev_dbg(&priv->i2c->dev, "%s(): invalid demod state %d\n",
			__func__, priv->state);
		return -EINVAL;
	}

	cxd2841er_write_reg(priv, I2C_SLVX, 0x00, 0x00);

	cxd2841er_write_reg(priv, I2C_SLVX, 0x15, 0x01);

	cxd2841er_write_reg(priv, I2C_SLVX, 0x17, 0x01);
	priv->state = STATE_SHUTDOWN;
	return 0;
}
