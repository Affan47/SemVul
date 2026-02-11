trinity_setup_uvd_clocks(struct radeon_device *rdev,
				     struct radeon_ps *new_rps,
				     struct radeon_ps *old_rps)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);

	if (pi->enable_gfx_power_gating) {
		trinity_gfx_powergating_enable(rdev, false);
	}

	if (pi->uvd_dpm) {
		if (trinity_uvd_clocks_zero(new_rps) &&
		    !trinity_uvd_clocks_zero(old_rps)) {
			trinity_setup_uvd_dpm_interval(rdev, 0);
		} else if (!trinity_uvd_clocks_zero(new_rps)) {
			trinity_setup_uvd_clock_table(rdev, new_rps);

			if (trinity_uvd_clocks_zero(old_rps)) {
				u32 tmp = RREG32(CG_MISC_REG);
				tmp &= 0xfffffffd;
				WREG32(CG_MISC_REG, tmp);

				radeon_set_uvd_clocks(rdev, new_rps->vclk, new_rps->dclk);

				trinity_setup_uvd_dpm_interval(rdev, 3000);
			}
		}
		trinity_uvd_dpm_config(rdev);
	} else {
		if (trinity_uvd_clocks_zero(new_rps) ||
		    trinity_uvd_clocks_equal(new_rps, old_rps))
			return;

		radeon_set_uvd_clocks(rdev, new_rps->vclk, new_rps->dclk);
	}

	if (pi->enable_gfx_power_gating) {
		trinity_gfx_powergating_enable(rdev, true);
	}
}
