get_pll_config(struct pll_limit *limits, int size,
	int clk)
{
	struct via_pll_config cur, up, down, best = {0, 1, 0};
	const u32 f0 = 14318180;
	int i, f;

	for (i = 0; i < size; i++) {
		cur.rshift = limits[i].rshift;
		cur.divisor = limits[i].divisor;
		cur.multiplier = clk / ((f0 / cur.divisor)>>cur.rshift);
		f = abs(get_pll_output_frequency(f0, cur) - clk);
		up = down = cur;
		up.multiplier++;
		down.multiplier--;
		if (abs(get_pll_output_frequency(f0, up) - clk) < f)
			cur = up;
		else if (abs(get_pll_output_frequency(f0, down) - clk) < f)
			cur = down;

		if (cur.multiplier < limits[i].multiplier_min)
			cur.multiplier = limits[i].multiplier_min;
		else if (cur.multiplier > limits[i].multiplier_max)
			cur.multiplier = limits[i].multiplier_max;

		f = abs(get_pll_output_frequency(f0, cur) - clk);
		if (f < abs(get_pll_output_frequency(f0, best) - clk))
			best = cur;
	}

	return best;
}
