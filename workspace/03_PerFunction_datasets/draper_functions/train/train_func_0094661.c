OPLL_new(uint32 clk, uint32 rate) {
	OPLL *opll;

	maketables(clk, rate);

	opll = (OPLL*)calloc(sizeof(OPLL), 1);
	if (opll == NULL)
		return NULL;

	opll->mask = 0;

	OPLL_reset(opll);

	return opll;
}
