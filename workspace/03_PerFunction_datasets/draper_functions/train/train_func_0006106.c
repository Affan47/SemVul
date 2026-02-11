tonga_dpm_force_state_pcie(struct pp_hwmgr *hwmgr, uint32_t n)
{
	tonga_hwmgr *data = (tonga_hwmgr *)(hwmgr->backend);


	PP_ASSERT_WITH_CODE(0 == tonga_is_dpm_running(hwmgr),
			"Trying to Force PCIE level when DPM is disabled", return -1;);
	if (0 == data->pcie_dpm_key_disabled)
		return (0 == smum_send_msg_to_smc_with_parameter(
							     hwmgr->smumgr,
			   (PPSMC_Msg)(PPSMC_MSG_PCIeDPM_ForceLevel),
								n) ? 0 : 1);

	return 0;
}
