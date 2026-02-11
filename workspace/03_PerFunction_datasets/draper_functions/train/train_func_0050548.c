kv_populate_samu_table(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	struct radeon_clock_voltage_dependency_table *table =
		&rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table;
	struct atom_clock_dividers dividers;
	int ret;
	u32 i;

	if (table == NULL || table->count == 0)
		return 0;

	pi->samu_level_count = 0;
	for (i = 0; i < table->count; i++) {
		if (pi->high_voltage_t &&
		    pi->high_voltage_t < table->entries[i].v)
			break;

		pi->samu_level[i].Frequency = cpu_to_be32(table->entries[i].clk);
		pi->samu_level[i].MinVoltage = cpu_to_be16(table->entries[i].v);

		pi->samu_level[i].ClkBypassCntl =
			(u8)kv_get_clk_bypass(rdev, table->entries[i].clk);

		ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
						     table->entries[i].clk, false, &dividers);
		if (ret)
			return ret;
		pi->samu_level[i].Divider = (u8)dividers.post_div;

		pi->samu_level_count++;
	}

	ret = kv_copy_bytes_to_smc(rdev,
				   pi->dpm_table_start +
				   offsetof(SMU7_Fusion_DpmTable, SamuLevelCount),
				   (u8 *)&pi->samu_level_count,
				   sizeof(u8),
				   pi->sram_end);
	if (ret)
		return ret;

	pi->samu_interval = 1;

	ret = kv_copy_bytes_to_smc(rdev,
				   pi->dpm_table_start +
				   offsetof(SMU7_Fusion_DpmTable, SAMUInterval),
				   (u8 *)&pi->samu_interval,
				   sizeof(u8),
				   pi->sram_end);
	if (ret)
		return ret;

	ret = kv_copy_bytes_to_smc(rdev,
				   pi->dpm_table_start +
				   offsetof(SMU7_Fusion_DpmTable, SamuLevel),
				   (u8 *)&pi->samu_level,
				   sizeof(SMU7_Fusion_ExtClkLevel) * SMU7_MAX_LEVELS_SAMU,
				   pi->sram_end);
	if (ret)
		return ret;

	return ret;
}
