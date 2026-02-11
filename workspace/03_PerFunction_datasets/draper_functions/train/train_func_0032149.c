fiji_print_current_perforce_level(
		struct pp_hwmgr *hwmgr, struct seq_file *m)
{
	uint32_t sclk, mclk, activity_percent = 0;
	uint32_t offset;
	struct fiji_hwmgr *data = (struct fiji_hwmgr *)(hwmgr->backend);

	smum_send_msg_to_smc(hwmgr->smumgr, PPSMC_MSG_API_GetSclkFrequency);

	sclk = cgs_read_register(hwmgr->device, mmSMC_MSG_ARG_0);

	smum_send_msg_to_smc(hwmgr->smumgr, PPSMC_MSG_API_GetMclkFrequency);

	mclk = cgs_read_register(hwmgr->device, mmSMC_MSG_ARG_0);
	seq_printf(m, "\n [  mclk  ]: %u MHz\n\n [  sclk  ]: %u MHz\n",
			mclk / 100, sclk / 100);

	offset = data->soft_regs_start + offsetof(SMU73_SoftRegisters, AverageGraphicsActivity);
	activity_percent = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, offset);
	activity_percent += 0x80;
	activity_percent >>= 8;

	seq_printf(m, "\n [GPU load]: %u%%\n\n", activity_percent > 100 ? 100 : activity_percent);
}
