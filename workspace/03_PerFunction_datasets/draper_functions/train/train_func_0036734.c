p5020_init_periph(struct clockgen *cg)
{
	u32 reg;
	int div = PLL_DIV2;

	reg = ioread32be(&cg->guts->rcwsr[7]);
	if (reg & RCWSR7_HWA_ASYNC_DIV)
		div = PLL_DIV4;

	if (reg & RCWSR7_FM1_CLK_SEL)
		cg->fman[0] = cg->pll[CGA_PLL2].div[div].clk;
	else
		cg->fman[0] = cg->pll[PLATFORM_PLL].div[PLL_DIV2].clk;
}
