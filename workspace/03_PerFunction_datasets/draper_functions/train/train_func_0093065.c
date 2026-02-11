ni_init_smc_table(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	int ret;
	struct radeon_ps *radeon_boot_state = rdev->pm.dpm.boot_ps;
	NISLANDS_SMC_STATETABLE *table = &ni_pi->smc_statetable;

	memset(table, 0, sizeof(NISLANDS_SMC_STATETABLE));

	ni_populate_smc_voltage_tables(rdev, table);

	switch (rdev->pm.int_thermal_type) {
	case THERMAL_TYPE_NI:
	case THERMAL_TYPE_EMC2103_WITH_INTERNAL:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_INTERNAL;
		break;
	case THERMAL_TYPE_NONE:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_NONE;
		break;
	default:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_EXTERNAL;
		break;
	}

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_HARDWAREDC)
		table->systemFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_REGULATOR_HOT)
		table->systemFlags |= PPSMC_SYSTEMFLAG_REGULATOR_HOT;

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
		table->systemFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	if (pi->mem_gddr5)
		table->systemFlags |= PPSMC_SYSTEMFLAG_GDDR5;

	ret = ni_populate_smc_initial_state(rdev, radeon_boot_state, table);
	if (ret)
		return ret;

	ret = ni_populate_smc_acpi_state(rdev, table);
	if (ret)
		return ret;

	table->driverState = table->initialState;

	table->ULVState = table->initialState;

	ret = ni_do_program_memory_timing_parameters(rdev, radeon_boot_state,
						     NISLANDS_INITIAL_STATE_ARB_INDEX);
	if (ret)
		return ret;

	return rv770_copy_bytes_to_smc(rdev, pi->state_table_start, (u8 *)table,
				       sizeof(NISLANDS_SMC_STATETABLE), pi->sram_end);
}
