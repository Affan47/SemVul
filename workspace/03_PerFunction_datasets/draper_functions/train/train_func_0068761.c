sp887x_read_ucblocks(struct dvb_frontend* fe, u32* ucblocks)
{
	struct sp887x_state* state = fe->demodulator_priv;

	*ucblocks = sp887x_readreg(state, 0xc0c);
	if (*ucblocks == 0xfff)
		*ucblocks = ~0;

	return 0;
}
