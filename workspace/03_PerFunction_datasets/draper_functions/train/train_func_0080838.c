stv0299_send_diseqc_burst(struct dvb_frontend *fe,
				     enum fe_sec_mini_cmd burst)
{
	struct stv0299_state* state = fe->demodulator_priv;
	u8 val;

	dprintk ("%s\n", __func__);

	if (stv0299_wait_diseqc_idle (state, 100) < 0)
		return -ETIMEDOUT;

	val = stv0299_readreg (state, 0x08);

	if (stv0299_writeregI (state, 0x08, (val & ~0x7) | 0x2))
		return -EREMOTEIO;

	if (stv0299_writeregI (state, 0x09, burst == SEC_MINI_A ? 0x00 : 0xff))
		return -EREMOTEIO;

	if (stv0299_wait_diseqc_idle (state, 100) < 0)
		return -ETIMEDOUT;

	if (stv0299_writeregI (state, 0x08, val))
		return -EREMOTEIO;

	return 0;
}
