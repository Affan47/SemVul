kv_enable_new_levels(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	u32 i;

	for (i = 0; i < SMU7_MAX_LEVELS_GRAPHICS; i++) {
		if (i >= pi->lowest_valid && i <= pi->highest_valid)
			kv_dpm_power_level_enable(rdev, i, true);
	}
}
