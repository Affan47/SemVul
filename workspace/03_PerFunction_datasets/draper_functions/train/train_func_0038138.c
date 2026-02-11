clk_divider_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *prate)
{
	struct clk_divider *divider = to_clk_divider(hw);
	int bestdiv;


	if (divider->flags & CLK_DIVIDER_READ_ONLY) {
		bestdiv = clk_readl(divider->reg) >> divider->shift;
		bestdiv &= div_mask(divider->width);
		bestdiv = _get_div(divider->table, bestdiv, divider->flags,
			divider->width);
		return DIV_ROUND_UP_ULL((u64)*prate, bestdiv);
	}

	return divider_round_rate(hw, rate, prate, divider->table,
				  divider->width, divider->flags);
}
