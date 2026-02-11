__clk_get_hw(struct clk *clk)
{
	return !clk ? NULL : clk->core->hw;
}
