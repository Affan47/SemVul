tonga_send_msg_to_smc_return_parameter(
		struct pp_hwmgr *hwmgr,
		PPSMC_Msg msg,
		uint32_t *parameter)
{
	int result;

	result = smum_send_msg_to_smc(hwmgr->smumgr, msg);

	if ((0 == result) && parameter) {
		*parameter = cgs_read_register(hwmgr->device, mmSMC_MSG_ARG_0);
	}

	return result;
}
