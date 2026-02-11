clk_pll_determine_rate(struct clk_hw *hw, struct clk_rate_request *req)
{
	struct clk_pll *pll = to_clk_pll(hw);
	const struct pll_freq_tbl *f;

	f = find_freq(pll->freq_tbl, req->rate);
	if (!f)
		req->rate = clk_pll_recalc_rate(hw, req->best_parent_rate);
	else
		req->rate = f->freq;

	return 0;
}
