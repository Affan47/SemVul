btc_dpm_get_sclk(struct radeon_device *rdev, bool low)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct rv7xx_ps *requested_state = rv770_get_ps(&eg_pi->requested_rps);

	if (low)
		return requested_state->low.sclk;
	else
		return requested_state->high.sclk;
}
