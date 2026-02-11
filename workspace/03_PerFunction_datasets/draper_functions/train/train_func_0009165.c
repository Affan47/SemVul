jdvbt90502_read_status(struct dvb_frontend *fe,
				  enum fe_status *state)
{
	u8 result;
	int ret;

	*state = FE_HAS_SIGNAL;

	ret = jdvbt90502_pll_read(fe->demodulator_priv, &result);
	if (ret) {
		deb_fe("%s:ret == %d\n", __func__, ret);
		return -EREMOTEIO;
	}

	*state = FE_HAS_SIGNAL
		| FE_HAS_CARRIER
		| FE_HAS_VITERBI
		| FE_HAS_SYNC;

	if (result & PLL_STATUS_LOCKED)
		*state |= FE_HAS_LOCK;

	return 0;
}
