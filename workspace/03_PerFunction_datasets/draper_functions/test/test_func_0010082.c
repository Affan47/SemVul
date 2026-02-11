dib7000m_reset_pll(struct dib7000m_state *state)
{
	const struct dibx000_bandwidth_config *bw = state->cfg.bw;
	u16 reg_907,reg_910;


	reg_907 = (bw->pll_bypass << 15) | (bw->modulo << 7) |
		(bw->ADClkSrc << 6) | (bw->IO_CLK_en_core << 5) | (bw->bypclk_div << 2) |
		(bw->enable_refdiv << 1) | (0 << 0);
	reg_910 = (((bw->pll_ratio >> 6) & 0x3) << 3) | (bw->pll_range << 1) | bw->pll_reset;


	if (!state->cfg.quartz_direct) {
		reg_910 |= (1 << 5);


		if(state->cfg.input_clk_is_div_2)
			reg_907 |= (16 << 9);
		else
			reg_907 |= (8 << 9);
	} else {
		reg_907 |= (bw->pll_ratio & 0x3f) << 9;
		reg_910 |= (bw->pll_prediv << 5);
	}

	dib7000m_write_word(state, 910, reg_910);
	dib7000m_write_word(state, 907, reg_907);
	dib7000m_write_word(state, 908, 0x0006);

	dib7000m_reset_pll_common(state, bw);
}
