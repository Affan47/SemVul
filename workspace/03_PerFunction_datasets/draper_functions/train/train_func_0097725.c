ci_update_vce_dpm(struct radeon_device *rdev,
			     struct radeon_ps *radeon_new_state,
			     struct radeon_ps *radeon_current_state)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	int ret = 0;
	u32 tmp;

	if (radeon_current_state->evclk != radeon_new_state->evclk) {
		if (radeon_new_state->evclk) {

			cik_update_cg(rdev, RADEON_CG_BLOCK_VCE, false);

			pi->smc_state_table.VceBootLevel = ci_get_vce_boot_level(rdev);
			tmp = RREG32_SMC(DPM_TABLE_475);
			tmp &= ~VceBootLevel_MASK;
			tmp |= VceBootLevel(pi->smc_state_table.VceBootLevel);
			WREG32_SMC(DPM_TABLE_475, tmp);

			ret = ci_enable_vce_dpm(rdev, true);
		} else {

			cik_update_cg(rdev, RADEON_CG_BLOCK_VCE, true);

			ret = ci_enable_vce_dpm(rdev, false);
		}
	}
	return ret;
}
