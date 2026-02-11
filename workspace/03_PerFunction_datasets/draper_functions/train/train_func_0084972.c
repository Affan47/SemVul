ci_populate_and_upload_sclk_mclk_dpm_levels(struct amdgpu_device *adev,
						       struct amdgpu_ps *amdgpu_state)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	struct ci_ps *state = ci_get_ps(amdgpu_state);
	u32 sclk = state->performance_levels[state->performance_level_count-1].sclk;
	u32 mclk = state->performance_levels[state->performance_level_count-1].mclk;
	struct ci_dpm_table *dpm_table = &pi->dpm_table;
	int ret;

	if (!pi->need_update_smu7_dpm_table)
		return 0;

	if (pi->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_SCLK)
		dpm_table->sclk_table.dpm_levels[dpm_table->sclk_table.count-1].value = sclk;

	if (pi->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_MCLK)
		dpm_table->mclk_table.dpm_levels[dpm_table->mclk_table.count-1].value = mclk;

	if (pi->need_update_smu7_dpm_table & (DPMTABLE_OD_UPDATE_SCLK | DPMTABLE_UPDATE_SCLK)) {
		ret = ci_populate_all_graphic_levels(adev);
		if (ret)
			return ret;
	}

	if (pi->need_update_smu7_dpm_table & (DPMTABLE_OD_UPDATE_MCLK | DPMTABLE_UPDATE_MCLK)) {
		ret = ci_populate_all_memory_levels(adev);
		if (ret)
			return ret;
	}

	return 0;
}
