tda8083_read_ucblocks(struct dvb_frontend* fe, u32* ucblocks)
{
	struct tda8083_state* state = fe->demodulator_priv;

	*ucblocks = tda8083_readreg(state, 0x0f);
	if (*ucblocks == 0xff)
		*ucblocks = 0xffffffff;

	return 0;
}
