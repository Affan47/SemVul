__clk_dyn_rcg_set_rate(struct clk_hw *hw, unsigned long rate)
{
	struct clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	const struct freq_tbl *f;

	f = qcom_find_freq(rcg->freq_tbl, rate);
	if (!f)
		return -EINVAL;

	return configure_bank(rcg, f);
}
