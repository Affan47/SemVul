tda18271_calc_rf_cal(struct dvb_frontend *fe, u32 *freq)
{

	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	u8 val;

	int ret = tda18271_lookup_map(fe, RF_CAL, freq, &val);


	if (ret < 0)
		goto fail;

	regs[R_EB14] = val;
fail:
	return ret;
}
