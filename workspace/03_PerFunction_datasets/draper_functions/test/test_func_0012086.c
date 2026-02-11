tonga_update_and_upload_mc_reg_table(struct pp_hwmgr *hwmgr)
{
	struct tonga_hwmgr *data = (struct tonga_hwmgr *)(hwmgr->backend);

	uint32_t address;
	int32_t result;

	if (0 == (data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_MCLK))
		return 0;


	memset(&data->mc_reg_table, 0, sizeof(SMU72_Discrete_MCRegisters));

	result = tonga_convert_mc_reg_table_to_smc(hwmgr, &(data->mc_reg_table));

	if(result != 0)
		return result;


	address = data->mc_reg_table_start + (uint32_t)offsetof(SMU72_Discrete_MCRegisters, data[0]);

	return  tonga_copy_bytes_to_smc(hwmgr->smumgr, address,
				 (uint8_t *)&data->mc_reg_table.data[0],
				sizeof(SMU72_Discrete_MCRegisterSet) * data->dpm_table.mclk_table.count,
				data->sram_end);
}
