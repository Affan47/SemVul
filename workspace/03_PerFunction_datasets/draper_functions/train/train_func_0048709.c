devm_clk_register(struct device *dev, struct clk_hw *hw)
{
	struct clk *clk;
	struct clk **clkp;

	clkp = devres_alloc(devm_clk_release, sizeof(*clkp), GFP_KERNEL);
	if (!clkp)
		return ERR_PTR(-ENOMEM);

	clk = clk_register(dev, hw);
	if (!IS_ERR(clk)) {
		*clkp = clk;
		devres_add(dev, clkp);
	} else {
		devres_free(clkp);
	}

	return clk;
}
