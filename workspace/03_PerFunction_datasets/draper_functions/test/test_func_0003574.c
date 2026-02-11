xc5000_is_firmware_loaded(struct dvb_frontend *fe)
{
	struct xc5000_priv *priv = fe->tuner_priv;
	int ret;
	u16 id;

	ret = xc5000_readreg(priv, XREG_PRODUCT_ID, &id);
	if (ret == 0) {
		if (id == XC_PRODUCT_ID_FW_NOT_LOADED)
			ret = -ENOENT;
		else
			ret = 0;
	}

	dprintk(1, "%s() returns %s id = 0x%x\n", __func__,
		ret == 0 ? "True" : "False", id);
	return ret;
}
