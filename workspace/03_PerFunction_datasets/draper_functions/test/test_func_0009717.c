s5h1420_read_ber(struct dvb_frontend* fe, u32* ber)
{
	struct s5h1420_state* state = fe->demodulator_priv;

	s5h1420_writereg(state, 0x46, 0x1d);
	mdelay(25);

	*ber = (s5h1420_readreg(state, 0x48) << 8) | s5h1420_readreg(state, 0x47);

	return 0;
}
