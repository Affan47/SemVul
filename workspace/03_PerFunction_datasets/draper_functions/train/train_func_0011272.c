legacy_pll_init(struct device_node *np, int idx)
{
	struct clockgen_pll *pll;
	struct clk_onecell_data *onecell_data;
	struct clk **subclks;
	int count, rc;

	legacy_init_clockgen(np);

	pll = &clockgen.pll[idx];
	count = of_property_count_strings(np, "clock-output-names");

	BUILD_BUG_ON(ARRAY_SIZE(pll->div) < 4);
	subclks = kcalloc(4, sizeof(struct clk *), GFP_KERNEL);
	if (!subclks)
		return;

	onecell_data = kmalloc(sizeof(*onecell_data), GFP_KERNEL);
	if (!onecell_data)
		goto err_clks;

	if (count <= 3) {
		subclks[0] = pll->div[0].clk;
		subclks[1] = pll->div[1].clk;
		subclks[2] = pll->div[3].clk;
	} else {
		subclks[0] = pll->div[0].clk;
		subclks[1] = pll->div[1].clk;
		subclks[2] = pll->div[2].clk;
		subclks[3] = pll->div[3].clk;
	}

	onecell_data->clks = subclks;
	onecell_data->clk_num = count;

	rc = of_clk_add_provider(np, of_clk_src_onecell_get, onecell_data);
	if (rc) {
		pr_err("%s: Couldn't register clk provider for node %s: %d\n",
		       __func__, np->name, rc);
		goto err_cell;
	}

	return;
err_cell:
	kfree(onecell_data);
err_clks:
	kfree(subclks);
}
