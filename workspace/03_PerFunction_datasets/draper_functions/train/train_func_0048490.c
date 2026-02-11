ni_calculate_adjusted_tdp_limits(struct radeon_device *rdev,
					    bool adjust_polarity,
					    u32 tdp_adjustment,
					    u32 *tdp_limit,
					    u32 *near_tdp_limit)
{
	if (tdp_adjustment > (u32)rdev->pm.dpm.tdp_od_limit)
		return -EINVAL;

	if (adjust_polarity) {
		*tdp_limit = ((100 + tdp_adjustment) * rdev->pm.dpm.tdp_limit) / 100;
		*near_tdp_limit = rdev->pm.dpm.near_tdp_limit + (*tdp_limit - rdev->pm.dpm.tdp_limit);
	} else {
		*tdp_limit = ((100 - tdp_adjustment) * rdev->pm.dpm.tdp_limit) / 100;
		*near_tdp_limit = rdev->pm.dpm.near_tdp_limit - (rdev->pm.dpm.tdp_limit - *tdp_limit);
	}

	return 0;
}
