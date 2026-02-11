cxd2820r_read_status_t2(struct dvb_frontend *fe, enum fe_status *status)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	int ret;
	u8 buf[1];
	*status = 0;

	ret = cxd2820r_rd_reg(priv, 0x02010 , &buf[0]);
	if (ret)
		goto error;

	if ((buf[0] & 0x07) == 6) {
		if (((buf[0] >> 5) & 0x01) == 1) {
			*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
		} else {
			*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC;
		}
	}

	dev_dbg(&priv->i2c->dev, "%s: lock=%02x\n", __func__, buf[0]);

	return ret;
error:
	dev_dbg(&priv->i2c->dev, "%s: failed=%d\n", __func__, ret);
	return ret;
}
