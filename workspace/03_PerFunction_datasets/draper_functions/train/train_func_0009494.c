tonga_start_in_non_protection_mode(struct pp_smumgr *smumgr)
{
	int result = 0;


	SMUM_WAIT_VFPF_INDIRECT_FIELD_UNEQUAL(smumgr, SMC_IND,
		RCU_UC_EVENTS, boot_seq_done, 0);


	cgs_write_ind_register(smumgr->device, CGS_IND_REG__SMC,
		ixFIRMWARE_FLAGS, 0);


	SMUM_WRITE_VFPF_INDIRECT_FIELD(smumgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 1);

	result = tonga_smu_upload_firmware_image(smumgr);

	if (result != 0)
		return result;


	tonga_program_jump_on_start(smumgr);


	SMUM_WRITE_VFPF_INDIRECT_FIELD(smumgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);


	SMUM_WRITE_VFPF_INDIRECT_FIELD(smumgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 0);


	SMUM_WAIT_VFPF_INDIRECT_FIELD(smumgr, SMC_IND,
		FIRMWARE_FLAGS, INTERRUPTS_ENABLED, 1);

	return result;
}
