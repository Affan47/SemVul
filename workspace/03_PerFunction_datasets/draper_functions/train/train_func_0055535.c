phm_force_dpm_levels(struct pp_hwmgr *hwmgr, enum amd_dpm_forced_level level)
{
	PHM_FUNC_CHECK(hwmgr);

	if (hwmgr->hwmgr_func->force_dpm_level != NULL)
		return hwmgr->hwmgr_func->force_dpm_level(hwmgr, level);

	return 0;
}
