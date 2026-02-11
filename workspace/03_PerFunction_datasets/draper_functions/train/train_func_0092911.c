cxd2841er_set_tone(struct dvb_frontend *fe,
			      enum fe_sec_tone_mode tone)
{
	u8 data;
	struct cxd2841er_priv *priv  = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s(): tone %s\n", __func__,
		(tone == SEC_TONE_ON ? "On" : "Off"));
	if (priv->state != STATE_SLEEP_S &&
			priv->state != STATE_ACTIVE_S) {
		dev_err(&priv->i2c->dev, "%s(): invalid demod state %d\n",
			__func__, priv->state);
		return -EINVAL;
	}
	data = (tone == SEC_TONE_ON ? 1 : 0);
	cxd2841er_write_reg(priv, I2C_SLVT, 0x00, 0xbb);
	cxd2841er_write_reg(priv, I2C_SLVT, 0x36, data);
	return 0;
}
