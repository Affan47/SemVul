cz_tf_enable_nb_dpm(struct pp_hwmgr *hwmgr,
					void *input, void *output,
					void *storage, int result)
{
	int ret = 0;

	struct cz_hwmgr *cz_hwmgr = (struct cz_hwmgr *)(hwmgr->backend);
	unsigned long dpm_features = 0;

	if (!cz_hwmgr->is_nb_dpm_enabled) {
		PP_DBG_LOG("enabling ALL SMU features.\n");
		dpm_features |= NB_DPM_MASK;
		ret = smum_send_msg_to_smc_with_parameter(
							     hwmgr->smumgr,
					 PPSMC_MSG_EnableAllSmuFeatures,
							     dpm_features);
		if (ret == 0)
			cz_hwmgr->is_nb_dpm_enabled = true;
	}

	return ret;
}
