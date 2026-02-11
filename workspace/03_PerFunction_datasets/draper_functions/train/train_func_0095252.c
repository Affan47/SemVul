rs780_dpm_debugfs_print_current_performance_level(struct radeon_device *rdev,
						       struct seq_file *m)
{
	struct radeon_ps *rps = rdev->pm.dpm.current_ps;
	struct igp_ps *ps = rs780_get_ps(rps);
	u32 current_fb_div = RREG32(FVTHROT_STATUS_REG0) & CURRENT_FEEDBACK_DIV_MASK;
	u32 func_cntl = RREG32(CG_SPLL_FUNC_CNTL);
	u32 ref_div = ((func_cntl & SPLL_REF_DIV_MASK) >> SPLL_REF_DIV_SHIFT) + 1;
	u32 post_div = ((func_cntl & SPLL_SW_HILEN_MASK) >> SPLL_SW_HILEN_SHIFT) + 1 +
		((func_cntl & SPLL_SW_LOLEN_MASK) >> SPLL_SW_LOLEN_SHIFT) + 1;
	u32 sclk = (rdev->clock.spll.reference_freq * current_fb_div) /
		(post_div * ref_div);

	seq_printf(m, "uvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);


	if (sclk < (ps->sclk_low + 500))
		seq_printf(m, "power level 0    sclk: %u vddc_index: %d\n",
			   ps->sclk_low, ps->min_voltage);
	else
		seq_printf(m, "power level 1    sclk: %u vddc_index: %d\n",
			   ps->sclk_high, ps->max_voltage);
}
