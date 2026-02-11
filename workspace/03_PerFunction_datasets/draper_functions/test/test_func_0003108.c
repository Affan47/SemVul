si_init_smc_spll_table(struct radeon_device *rdev)
{
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);
	SMC_SISLANDS_SPLL_DIV_TABLE *spll_table;
	SISLANDS_SMC_SCLK_VALUE sclk_params;
	u32 fb_div, p_div;
	u32 clk_s, clk_v;
	u32 sclk = 0;
	int ret = 0;
	u32 tmp;
	int i;

	if (si_pi->spll_table_start == 0)
		return -EINVAL;

	spll_table = kzalloc(sizeof(SMC_SISLANDS_SPLL_DIV_TABLE), GFP_KERNEL);
	if (spll_table == NULL)
		return -ENOMEM;

	for (i = 0; i < 256; i++) {
		ret = si_calculate_sclk_params(rdev, sclk, &sclk_params);
		if (ret)
			break;

		p_div = (sclk_params.vCG_SPLL_FUNC_CNTL & SPLL_PDIV_A_MASK) >> SPLL_PDIV_A_SHIFT;
		fb_div = (sclk_params.vCG_SPLL_FUNC_CNTL_3 & SPLL_FB_DIV_MASK) >> SPLL_FB_DIV_SHIFT;
		clk_s = (sclk_params.vCG_SPLL_SPREAD_SPECTRUM & CLK_S_MASK) >> CLK_S_SHIFT;
		clk_v = (sclk_params.vCG_SPLL_SPREAD_SPECTRUM_2 & CLK_V_MASK) >> CLK_V_SHIFT;

		fb_div &= ~0x00001FFF;
		fb_div >>= 1;
		clk_v >>= 6;

		if (p_div & ~(SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_SHIFT))
			ret = -EINVAL;
		if (fb_div & ~(SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_SHIFT))
			ret = -EINVAL;
		if (clk_s & ~(SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_SHIFT))
			ret = -EINVAL;
		if (clk_v & ~(SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_SHIFT))
			ret = -EINVAL;

		if (ret)
			break;

		tmp = ((fb_div << SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_MASK) |
			((p_div << SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_MASK);
		spll_table->freq[i] = cpu_to_be32(tmp);

		tmp = ((clk_v << SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_MASK) |
			((clk_s << SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_MASK);
		spll_table->ss[i] = cpu_to_be32(tmp);

		sclk += 512;
	}


	if (!ret)
		ret = si_copy_bytes_to_smc(rdev, si_pi->spll_table_start,
					   (u8 *)spll_table, sizeof(SMC_SISLANDS_SPLL_DIV_TABLE),
					   si_pi->sram_end);

	if (ret)
		ni_pi->enable_power_containment = false;

	kfree(spll_table);

	return ret;
}
