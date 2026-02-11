cz_phm_unforce_dpm_levels(struct pp_hwmgr *hwmgr)
{
	struct cz_hwmgr *cz_hwmgr = (struct cz_hwmgr *)(hwmgr->backend);
	struct phm_clock_voltage_dependency_table *table =
				hwmgr->dyn_state.vddc_dependency_on_sclk;
	unsigned long clock = 0, level;

	if (NULL == table || table->count <= 0)
		return -EINVAL;

	cz_hwmgr->sclk_dpm.soft_min_clk = table->entries[0].clk;
	cz_hwmgr->sclk_dpm.hard_min_clk = table->entries[0].clk;

	level = cz_get_max_sclk_level(hwmgr) - 1;

	if (level < table->count)
		clock = table->entries[level].clk;
	else
		clock = table->entries[table->count - 1].clk;

	cz_hwmgr->sclk_dpm.soft_max_clk = clock;
	cz_hwmgr->sclk_dpm.hard_max_clk = clock;

	smum_send_msg_to_smc_with_parameter(hwmgr->smumgr,
				PPSMC_MSG_SetSclkSoftMin,
				cz_get_sclk_level(hwmgr,
				cz_hwmgr->sclk_dpm.soft_min_clk,
				PPSMC_MSG_SetSclkSoftMin));

	smum_send_msg_to_smc_with_parameter(hwmgr->smumgr,
				PPSMC_MSG_SetSclkSoftMax,
				cz_get_sclk_level(hwmgr,
				cz_hwmgr->sclk_dpm.soft_max_clk,
				PPSMC_MSG_SetSclkSoftMax));

	return 0;
}
