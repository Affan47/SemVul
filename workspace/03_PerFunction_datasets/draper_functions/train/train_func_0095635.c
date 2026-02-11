dib8096p_tuner_sleep(struct dvb_frontend *fe, int onoff)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 en_cur_state;

	dprintk("sleep dib8096p: %d", onoff);

	en_cur_state = dib8000_read_word(state, 1922);


	if (en_cur_state > 0xff)
		state->tuner_enable = en_cur_state ;

	if (onoff)
		en_cur_state &= 0x00ff;
	else {
		if (state->tuner_enable != 0)
			en_cur_state = state->tuner_enable;
	}

	dib8000_write_word(state, 1922, en_cur_state);

	return 0;
}
