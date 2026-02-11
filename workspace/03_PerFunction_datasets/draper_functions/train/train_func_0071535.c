trinity_get_valid_engine_clock(struct radeon_device *rdev,
					  u32 lower_limit)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	u32 i;

	for (i = 0; i < pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries; i++) {
		if (pi->sys_info.sclk_voltage_mapping_table.entries[i].sclk_frequency >= lower_limit)
			return pi->sys_info.sclk_voltage_mapping_table.entries[i].sclk_frequency;
	}

	if (i == pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries)
		DRM_ERROR("engine clock out of range!");

	return 0;
}
