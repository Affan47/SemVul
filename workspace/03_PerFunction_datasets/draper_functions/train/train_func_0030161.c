fiji_request_smu_load_fw(struct pp_smumgr *smumgr)
{
	struct fiji_smumgr *priv = (struct fiji_smumgr *)(smumgr->backend);
	uint32_t fw_to_load;
	struct SMU_DRAMData_TOC *toc;

	if (priv->soft_regs_start)
		cgs_write_ind_register(smumgr->device, CGS_IND_REG__SMC,
				priv->soft_regs_start +
				offsetof(SMU73_SoftRegisters, UcodeLoadStatus),
				0x0);

	toc = (struct SMU_DRAMData_TOC *)priv->header;
	toc->num_entries = 0;
	toc->structure_version = 1;

	PP_ASSERT_WITH_CODE(
			0 == fiji_populate_single_firmware_entry(smumgr,
					UCODE_ID_RLC_G, &toc->entry[toc->num_entries++]),
			"Failed to Get Firmware Entry.\n" , return -1 );
	PP_ASSERT_WITH_CODE(
			0 == fiji_populate_single_firmware_entry(smumgr,
					UCODE_ID_CP_CE, &toc->entry[toc->num_entries++]),
			"Failed to Get Firmware Entry.\n" , return -1 );
	PP_ASSERT_WITH_CODE(
			0 == fiji_populate_single_firmware_entry(smumgr,
					UCODE_ID_CP_PFP, &toc->entry[toc->num_entries++]),
			"Failed to Get Firmware Entry.\n" , return -1 );
	PP_ASSERT_WITH_CODE(
			0 == fiji_populate_single_firmware_entry(smumgr,
					UCODE_ID_CP_ME, &toc->entry[toc->num_entries++]),
			"Failed to Get Firmware Entry.\n" , return -1 );
	PP_ASSERT_WITH_CODE(
			0 == fiji_populate_single_firmware_entry(smumgr,
					UCODE_ID_CP_MEC, &toc->entry[toc->num_entries++]),
			"Failed to Get Firmware Entry.\n" , return -1 );
	PP_ASSERT_WITH_CODE(
			0 == fiji_populate_single_firmware_entry(smumgr,
					UCODE_ID_CP_MEC_JT1, &toc->entry[toc->num_entries++]),
					"Failed to Get Firmware Entry.\n" , return -1 );
	PP_ASSERT_WITH_CODE(
			0 == fiji_populate_single_firmware_entry(smumgr,
					UCODE_ID_CP_MEC_JT2, &toc->entry[toc->num_entries++]),
					"Failed to Get Firmware Entry.\n" , return -1 );
	PP_ASSERT_WITH_CODE(
			0 == fiji_populate_single_firmware_entry(smumgr,
					UCODE_ID_SDMA0, &toc->entry[toc->num_entries++]),
					"Failed to Get Firmware Entry.\n" , return -1 );
	PP_ASSERT_WITH_CODE(
			0 == fiji_populate_single_firmware_entry(smumgr,
					UCODE_ID_SDMA1, &toc->entry[toc->num_entries++]),
					"Failed to Get Firmware Entry.\n" , return -1 );

	fiji_send_msg_to_smc_with_parameter(smumgr, PPSMC_MSG_DRV_DRAM_ADDR_HI,
			priv->header_buffer.mc_addr_high);
	fiji_send_msg_to_smc_with_parameter(smumgr,PPSMC_MSG_DRV_DRAM_ADDR_LO,
			priv->header_buffer.mc_addr_low);

	fw_to_load = UCODE_ID_RLC_G_MASK
			+ UCODE_ID_SDMA0_MASK
			+ UCODE_ID_SDMA1_MASK
			+ UCODE_ID_CP_CE_MASK
			+ UCODE_ID_CP_ME_MASK
			+ UCODE_ID_CP_PFP_MASK
			+ UCODE_ID_CP_MEC_MASK
			+ UCODE_ID_CP_MEC_JT1_MASK
			+ UCODE_ID_CP_MEC_JT2_MASK;

	if (fiji_send_msg_to_smc_with_parameter(smumgr,
			PPSMC_MSG_LoadUcodes, fw_to_load))
		printk(KERN_ERR "Fail to Request SMU Load uCode");

	return 0;
}
