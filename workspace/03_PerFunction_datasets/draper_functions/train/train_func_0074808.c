stv0299_read_signal_strength(struct dvb_frontend* fe, u16* strength)
{
	struct stv0299_state* state = fe->demodulator_priv;

	s32 signal =  0xffff - ((stv0299_readreg (state, 0x18) << 8)
			       | stv0299_readreg (state, 0x19));

	dprintk ("%s : FE_READ_SIGNAL_STRENGTH : AGC2I: 0x%02x%02x, signal=0x%04x\n", __func__,
		 stv0299_readreg (state, 0x18),
		 stv0299_readreg (state, 0x19), (int) signal);

	signal = signal * 5 / 4;
	*strength = (signal > 0xffff) ? 0xffff : (signal < 0) ? 0 : signal;

	return 0;
}
