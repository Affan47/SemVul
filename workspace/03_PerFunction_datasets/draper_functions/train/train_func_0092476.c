intel_lpss_unregister_clock_tree(struct clk *clk)
{
	struct clk *parent;

	while (clk) {
		parent = clk_get_parent(clk);
		clk_unregister(clk);
		clk = parent;
	}
}
