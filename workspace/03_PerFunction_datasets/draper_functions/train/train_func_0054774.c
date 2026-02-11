cxd2841er_active_s_to_sleep_s(struct cxd2841er_priv *priv)
{
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	if (priv->state != STATE_ACTIVE_S) {
		dev_err(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		return -EINVAL;
	}

	cxd2841er_write_reg(priv, I2C_SLVT, 0x00, 0x00);

	cxd2841er_write_reg(priv, I2C_SLVT, 0xc3, 0x01);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x80, 0x1f);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x81, 0xff);

	cxd2841er_write_reg(priv, I2C_SLVX, 0x00, 0x00);

	cxd2841er_write_reg(priv, I2C_SLVX, 0x18, 0x01);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x00, 0x00);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x31, 0x00);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x63, 0x16);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x65, 0x27);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x69, 0x06);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x2c, 0x00);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x00, 0xae);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x30, 0x00);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x00, 0x00);

	cxd2841er_write_reg(priv, I2C_SLVT, 0x2d, 0x00);
	priv->state = STATE_SLEEP_S;
	return 0;
}
