xc4000_get_status(struct dvb_frontend *fe, u32 *status)
{
	struct xc4000_priv *priv = fe->tuner_priv;
	u16	lock_status = 0;

	mutex_lock(&priv->lock);

	if (priv->cur_fw.type & BASE)
		xc_get_lock_status(priv, &lock_status);

	*status = (lock_status == 1 ?
		   TUNER_STATUS_LOCKED | TUNER_STATUS_STEREO : 0);
	if (priv->cur_fw.type & (DTV6 | DTV7 | DTV78 | DTV8))
		*status &= (~TUNER_STATUS_STEREO);

	mutex_unlock(&priv->lock);

	dprintk(2, "%s() lock_status = %d\n", __func__, lock_status);

	return 0;
}
