wm831x_fll_round_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long *unused)
{
	int best = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(wm831x_fll_auto_rates); i++)
		if (abs(wm831x_fll_auto_rates[i] - rate) <
		    abs(wm831x_fll_auto_rates[best] - rate))
			best = i;

	return wm831x_fll_auto_rates[best];
}
