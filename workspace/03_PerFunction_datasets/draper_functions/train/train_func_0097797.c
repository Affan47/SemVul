stv0367cab_get_mclk(struct dvb_frontend *fe, u32 ExtClk_Hz)
{
	struct stv0367_state *state = fe->demodulator_priv;
	u32 mclk_Hz = 0;
	u32 M, N, P;


	if (stv0367_readbits(state, F367CAB_BYPASS_PLLXN) == 0) {
		N = (u32)stv0367_readbits(state, F367CAB_PLL_NDIV);
		if (N == 0)
			N = N + 1;

		M = (u32)stv0367_readbits(state, F367CAB_PLL_MDIV);
		if (M == 0)
			M = M + 1;

		P = (u32)stv0367_readbits(state, F367CAB_PLL_PDIV);

		if (P > 5)
			P = 5;

		mclk_Hz = ((ExtClk_Hz / 2) * N) / (M * (1 << P));
		dprintk("stv0367cab_get_mclk BYPASS_PLLXN mclk_Hz=%d\n",
								mclk_Hz);
	} else
		mclk_Hz = ExtClk_Hz;

	dprintk("stv0367cab_get_mclk final mclk_Hz=%d\n", mclk_Hz);

	return mclk_Hz;
}
