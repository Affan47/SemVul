xc5000_get_if_frequency(struct dvb_frontend *fe, u32 *freq)
{
	struct xc5000_priv *priv = fe->tuner_priv;
	dprintk(1, "%s()\n", __func__);
	*freq = priv->if_khz * 1000;
	return 0;
}
