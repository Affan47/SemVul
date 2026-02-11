tonga_unfreeze_sclk_mclk_dpm(struct pp_hwmgr *hwmgr)
{
	struct tonga_hwmgr *data = (struct tonga_hwmgr *)(hwmgr->backend);

	if (0 == data->need_update_smu7_dpm_table)
		return 0;

	if ((0 == data->sclk_dpm_key_disabled) &&
		(data->need_update_smu7_dpm_table &
		(DPMTABLE_OD_UPDATE_SCLK + DPMTABLE_UPDATE_SCLK))) {

		PP_ASSERT_WITH_CODE(true == tonga_is_dpm_running(hwmgr),
			"Trying to Unfreeze SCLK DPM when DPM is disabled",
			);
		PP_ASSERT_WITH_CODE(
			 0 == smum_send_msg_to_smc(hwmgr->smumgr,
					 PPSMC_MSG_SCLKDPM_UnfreezeLevel),
			"Failed to unfreeze SCLK DPM during UnFreezeSclkMclkDPM Function!",
			return -1);
	}

	if ((0 == data->mclk_dpm_key_disabled) &&
		(data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_MCLK)) {

		PP_ASSERT_WITH_CODE(
				true == tonga_is_dpm_running(hwmgr),
				"Trying to Unfreeze MCLK DPM when DPM is disabled",
				);
		PP_ASSERT_WITH_CODE(
			 0 == smum_send_msg_to_smc(hwmgr->smumgr,
					 PPSMC_MSG_SCLKDPM_UnfreezeLevel),
		    "Failed to unfreeze MCLK DPM during UnFreezeSclkMclkDPM Function!",
		    return -1);
	}

	data->need_update_smu7_dpm_table = 0;

	return 0;
}
