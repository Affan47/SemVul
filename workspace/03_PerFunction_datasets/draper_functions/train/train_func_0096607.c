dib8000_set_bandwidth(struct dvb_frontend *fe, u32 bw)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u32 timf;

	if (bw == 0)
		bw = 6000;

	if (state->timf == 0) {
		dprintk("using default timf");
		timf = state->timf_default;
	} else {
		dprintk("using updated timf");
		timf = state->timf;
	}

	dib8000_write_word(state, 29, (u16) ((timf >> 16) & 0xffff));
	dib8000_write_word(state, 30, (u16) ((timf) & 0xffff));

	return 0;
}
