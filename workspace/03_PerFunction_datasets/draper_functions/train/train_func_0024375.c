cx24110_set_fec(struct cx24110_state *state, enum fe_code_rate fec)
{
	static const int rate[FEC_AUTO] = {-1,    1,    2,    3,    5,    7, -1};
	static const int g1[FEC_AUTO]   = {-1, 0x01, 0x02, 0x05, 0x15, 0x45, -1};
	static const int g2[FEC_AUTO]   = {-1, 0x01, 0x03, 0x06, 0x1a, 0x7a, -1};


	if (fec > FEC_AUTO)
		fec = FEC_AUTO;

	if (fec == FEC_AUTO) {
		cx24110_writereg(state, 0x37, cx24110_readreg(state, 0x37) & 0xdf);

		cx24110_writereg(state, 0x18, 0xae);

		cx24110_writereg(state, 0x05, (cx24110_readreg(state, 0x05) & 0xf0) | 0x3);

		cx24110_writereg(state, 0x22, (cx24110_readreg(state, 0x22) & 0xf0) | 0x3);

		cx24110_writereg(state, 0x1a, 0x05);
		cx24110_writereg(state, 0x1b, 0x06);

		return 0;
	} else {
		cx24110_writereg(state, 0x37, cx24110_readreg(state, 0x37) | 0x20);

		if (rate[fec] < 0)
			return -EINVAL;

		cx24110_writereg(state, 0x05, (cx24110_readreg(state, 0x05) & 0xf0) | rate[fec]);

		cx24110_writereg(state, 0x22, (cx24110_readreg(state, 0x22) & 0xf0) | rate[fec]);

		cx24110_writereg(state, 0x1a, g1[fec]);
		cx24110_writereg(state, 0x1b, g2[fec]);

	}
	return 0;
}
