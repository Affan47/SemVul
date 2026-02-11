dib0090_dcc_freq(struct dvb_frontend *fe, u8 fast)
{
	struct dib0090_state *state = fe->tuner_priv;
	if (fast)
		dib0090_write_reg(state, 0x04, 0);
	else
		dib0090_write_reg(state, 0x04, 1);
}
