xc4000_get_bandwidth(struct dvb_frontend *fe, u32 *bw)
{
	struct xc4000_priv *priv = fe->tuner_priv;
	dprintk(1, "%s()\n", __func__);

	*bw = priv->bandwidth;
	return 0;
}
