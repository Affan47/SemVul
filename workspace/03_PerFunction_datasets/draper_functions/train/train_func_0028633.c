fiji_dpm_force_dpm_level(struct pp_hwmgr *hwmgr,
				enum amd_dpm_forced_level level)
{
	int ret = 0;

	switch (level) {
	case AMD_DPM_FORCED_LEVEL_HIGH:
		ret = fiji_force_dpm_highest(hwmgr);
		if (ret)
			return ret;
		break;
	case AMD_DPM_FORCED_LEVEL_LOW:
		ret = fiji_force_dpm_lowest(hwmgr);
		if (ret)
			return ret;
		break;
	case AMD_DPM_FORCED_LEVEL_AUTO:
		ret = fiji_unforce_dpm_levels(hwmgr);
		if (ret)
			return ret;
		break;
	default:
		break;
	}

	hwmgr->dpm_level = level;

	return ret;
}
