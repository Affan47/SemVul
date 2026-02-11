tda8290_i2c_bridge(struct dvb_frontend *fe, int close)
{
	struct tda8290_priv *priv = fe->analog_demod_priv;

	unsigned char  enable[2] = { 0x21, 0xC0 };
	unsigned char disable[2] = { 0x21, 0x00 };
	unsigned char *msg;

	if (close) {
		msg = enable;
		tuner_i2c_xfer_send(&priv->i2c_props, msg, 2);

		msleep(20);
	} else {
		msg = disable;
		tuner_i2c_xfer_send(&priv->i2c_props, msg, 2);
	}

	return 0;
}
