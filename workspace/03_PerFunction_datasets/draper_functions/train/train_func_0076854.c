mux_get_parent(struct clk_hw *hw)
{
	struct mux_hwclock *hwc = to_mux_hwclock(hw);
	u32 clksel;
	s8 ret;

	clksel = (cg_in(hwc->cg, hwc->reg) & CLKSEL_MASK) >> CLKSEL_SHIFT;

	ret = hwc->clksel_to_parent[clksel];
	if (ret < 0) {
		pr_err("%s: mux at %p has bad clksel\n", __func__, hwc->reg);
		return 0;
	}

	return ret;
}
