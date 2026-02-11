cx24113_set_frequency(struct cx24113_state *state, u32 frequency)
{
	u8 r = 1;
	u16 n = 6;
	s32 f = 0;

	r = cx24113_readreg(state, 0x14);
	cx24113_writereg(state, 0x14, r & 0x3f);

	r = cx24113_readreg(state, 0x10);
	cx24113_writereg(state, 0x10, r & 0xbf);

	state->frequency = frequency;

	dprintk("tuning to frequency: %d\n", frequency);

	cx24113_calc_pll_nf(state, &n, &f);
	cx24113_set_nfr(state, n, f, state->refdiv);

	r = cx24113_readreg(state, 0x18) & 0xbf;
	if (state->vcodiv != VCODIV2)
		r |= 1 << 6;
	cx24113_writereg(state, 0x18, r);


	msleep(5);

	r = cx24113_readreg(state, 0x1c) & 0xef;
	cx24113_writereg(state, 0x1c, r | (1 << 4));
	return 0;
}
