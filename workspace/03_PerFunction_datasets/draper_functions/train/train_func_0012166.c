tonga_send_msg_to_smc_with_parameter(struct pp_smumgr *smumgr,
				uint16_t msg, uint32_t parameter)
{
	if (smumgr == NULL || smumgr->device == NULL)
		return -EINVAL;

	if (!tonga_is_smc_ram_running(smumgr))
		return PPSMC_Result_Failed;

	SMUM_WAIT_FIELD_UNEQUAL(smumgr, SMC_RESP_0, SMC_RESP, 0);
	cgs_write_register(smumgr->device, mmSMC_MSG_ARG_0, parameter);

	return tonga_send_msg_to_smc(smumgr, msg);
}
