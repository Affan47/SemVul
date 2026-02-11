ci_calculate_sclk_params(struct radeon_device *rdev,
				    u32 engine_clock,
				    SMU7_Discrete_GraphicsLevel *sclk)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct atom_clock_dividers dividers;
	u32 spll_func_cntl_3 = pi->clock_registers.cg_spll_func_cntl_3;
	u32 spll_func_cntl_4 = pi->clock_registers.cg_spll_func_cntl_4;
	u32 cg_spll_spread_spectrum = pi->clock_registers.cg_spll_spread_spectrum;
	u32 cg_spll_spread_spectrum_2 = pi->clock_registers.cg_spll_spread_spectrum_2;
	u32 reference_clock = rdev->clock.spll.reference_freq;
	u32 reference_divider;
	u32 fbdiv;
	int ret;

	ret = radeon_atom_get_clock_dividers(rdev,
					     COMPUTE_GPUCLK_INPUT_FLAG_SCLK,
					     engine_clock, false, &dividers);
	if (ret)
		return ret;

	reference_divider = 1 + dividers.ref_div;
	fbdiv = dividers.fb_div & 0x3FFFFFF;

	spll_func_cntl_3 &= ~SPLL_FB_DIV_MASK;
	spll_func_cntl_3 |= SPLL_FB_DIV(fbdiv);
        spll_func_cntl_3 |= SPLL_DITHEN;

	if (pi->caps_sclk_ss_support) {
		struct radeon_atom_ss ss;
		u32 vco_freq = engine_clock * dividers.post_div;

		if (radeon_atombios_get_asic_ss_info(rdev, &ss,
						     ASIC_INTERNAL_ENGINE_SS, vco_freq)) {
			u32 clk_s = reference_clock * 5 / (reference_divider * ss.rate);
			u32 clk_v = 4 * ss.percentage * fbdiv / (clk_s * 10000);

			cg_spll_spread_spectrum &= ~CLK_S_MASK;
			cg_spll_spread_spectrum |= CLK_S(clk_s);
			cg_spll_spread_spectrum |= SSEN;

			cg_spll_spread_spectrum_2 &= ~CLK_V_MASK;
			cg_spll_spread_spectrum_2 |= CLK_V(clk_v);
		}
	}

	sclk->SclkFrequency = engine_clock;
	sclk->CgSpllFuncCntl3 = spll_func_cntl_3;
	sclk->CgSpllFuncCntl4 = spll_func_cntl_4;
	sclk->SpllSpreadSpectrum = cg_spll_spread_spectrum;
	sclk->SpllSpreadSpectrum2  = cg_spll_spread_spectrum_2;
	sclk->SclkDid = (u8)dividers.post_divider;

	return 0;
}
