s5h1409_set_spectralinversion(struct dvb_frontend *fe, int inverted)
{
	struct s5h1409_state *state = fe->demodulator_priv;

	dprintk("%s(%d)\n", __func__, inverted);

	if (inverted == 1)
		return s5h1409_writereg(state, 0x1b, 0x1101);
	else
		return s5h1409_writereg(state, 0x1b, 0x0110);
}
