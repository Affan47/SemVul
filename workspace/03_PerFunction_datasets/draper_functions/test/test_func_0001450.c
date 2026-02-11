kv_set_enabled_levels(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	u32 i, new_mask = 0;

	for (i = pi->lowest_valid; i <= pi->highest_valid; i++)
		new_mask |= (1 << i);

	return kv_send_msg_to_smc_with_parameter(rdev,
						 PPSMC_MSG_SCLKDPM_SetEnabledMask,
						 new_mask);
}
