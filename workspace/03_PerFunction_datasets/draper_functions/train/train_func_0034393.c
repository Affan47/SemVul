wl18xx_set_clk(struct wl1271 *wl)
{
	u16 clk_freq;
	int ret;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_TOP_PRCM_ELP_SOC]);
	if (ret < 0)
		goto out;


	ret = wl18xx_top_reg_read(wl, PRIMARY_CLK_DETECT, &clk_freq);
	if (ret < 0)
		goto out;

	wl1271_debug(DEBUG_BOOT, "clock freq %d (%d, %d, %d, %d, %s)", clk_freq,
		     wl18xx_clk_table[clk_freq].n, wl18xx_clk_table[clk_freq].m,
		     wl18xx_clk_table[clk_freq].p, wl18xx_clk_table[clk_freq].q,
		     wl18xx_clk_table[clk_freq].swallow ? "swallow" : "spit");


	ret = wl18xx_top_reg_write(wl, PLLSH_COEX_PLL_N,
				   wl18xx_clk_table_coex[clk_freq].n);
	if (ret < 0)
		goto out;

	ret = wl18xx_top_reg_write(wl, PLLSH_COEX_PLL_M,
				   wl18xx_clk_table_coex[clk_freq].m);
	if (ret < 0)
		goto out;


	ret = wl18xx_top_reg_write(wl, PLLSH_COEX_PLL_SWALLOW_EN,
				   PLLSH_COEX_PLL_SWALLOW_EN_VAL1);
	if (ret < 0)
		goto out;

	ret = wl18xx_top_reg_write(wl, PLLSH_WCS_PLL_N,
				   wl18xx_clk_table[clk_freq].n);
	if (ret < 0)
		goto out;

	ret = wl18xx_top_reg_write(wl, PLLSH_WCS_PLL_M,
				   wl18xx_clk_table[clk_freq].m);
	if (ret < 0)
		goto out;

	if (wl18xx_clk_table[clk_freq].swallow) {

		ret = wl18xx_top_reg_write(wl, PLLSH_WCS_PLL_Q_FACTOR_CFG_1,
					   wl18xx_clk_table[clk_freq].q &
					   PLLSH_WCS_PLL_Q_FACTOR_CFG_1_MASK);
		if (ret < 0)
			goto out;


		ret = wl18xx_top_reg_write(wl, PLLSH_WCS_PLL_Q_FACTOR_CFG_2,
					(wl18xx_clk_table[clk_freq].q >> 16) &
					PLLSH_WCS_PLL_Q_FACTOR_CFG_2_MASK);
		if (ret < 0)
			goto out;


		ret = wl18xx_top_reg_write(wl, PLLSH_WCS_PLL_P_FACTOR_CFG_1,
					   wl18xx_clk_table[clk_freq].p &
					   PLLSH_WCS_PLL_P_FACTOR_CFG_1_MASK);
		if (ret < 0)
			goto out;


		ret = wl18xx_top_reg_write(wl, PLLSH_WCS_PLL_P_FACTOR_CFG_2,
					(wl18xx_clk_table[clk_freq].p >> 16) &
					PLLSH_WCS_PLL_P_FACTOR_CFG_2_MASK);
	} else {
		ret = wl18xx_top_reg_write(wl, PLLSH_WCS_PLL_SWALLOW_EN,
					   PLLSH_WCS_PLL_SWALLOW_EN_VAL2);
	}


	ret = wl18xx_top_reg_write(wl, PLLSH_WL_PLL_SEL,
				   PLLSH_WL_PLL_SEL_WCS_PLL);
	if (ret < 0)
		goto out;


	ret = wl18xx_top_reg_write(wl, PLLSH_WL_PLL_EN, PLLSH_WL_PLL_EN_VAL1);
	if (ret < 0)
		goto out;

	udelay(1000);


	ret = wl18xx_top_reg_write(wl, PLLSH_WL_PLL_EN, PLLSH_WL_PLL_EN_VAL2);
	if (ret < 0)
		goto out;


	ret = wl18xx_top_reg_write(wl, PLLSH_COEX_PLL_SWALLOW_EN,
				   PLLSH_COEX_PLL_SWALLOW_EN_VAL2);
	if (ret < 0)
		goto out;

out:
	return ret;
}
