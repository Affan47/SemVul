arizona_clk32k_disable(struct arizona *arizona)
{
	mutex_lock(&arizona->clk_lock);

	BUG_ON(arizona->clk32k_ref <= 0);

	arizona->clk32k_ref--;

	if (arizona->clk32k_ref == 0) {
		regmap_update_bits(arizona->regmap, ARIZONA_CLOCK_32K_1,
				   ARIZONA_CLK_32K_ENA, 0);

		switch (arizona->pdata.clk32k_src) {
		case ARIZONA_32KZ_MCLK1:
			pm_runtime_put_sync(arizona->dev);
			break;
		}
	}

	mutex_unlock(&arizona->clk_lock);

	return 0;
}
