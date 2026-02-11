fiji_populate_smc_initailial_state(struct pp_hwmgr *hwmgr)
{
	struct fiji_hwmgr *data = (struct fiji_hwmgr *)(hwmgr->backend);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);
	uint8_t count, level;

	count = (uint8_t)(table_info->vdd_dep_on_sclk->count);
	for (level = 0; level < count; level++) {
		if(table_info->vdd_dep_on_sclk->entries[level].clk >=
				data->vbios_boot_state.sclk_bootup_value) {
			data->smc_state_table.GraphicsBootLevel = level;
			break;
		}
	}

	count = (uint8_t)(table_info->vdd_dep_on_mclk->count);
	for (level = 0; level < count; level++) {
		if(table_info->vdd_dep_on_mclk->entries[level].clk >=
				data->vbios_boot_state.mclk_bootup_value) {
			data->smc_state_table.MemoryBootLevel = level;
			break;
		}
	}

	return 0;
}
