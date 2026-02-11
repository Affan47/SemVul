tonga_populate_initial_mc_reg_table(struct pp_hwmgr *hwmgr)
{
	int result;
	struct tonga_hwmgr *data = (struct tonga_hwmgr *)(hwmgr->backend);

	memset(&data->mc_reg_table, 0x00, sizeof(SMU72_Discrete_MCRegisters));
	result = tonga_populate_mc_reg_address(hwmgr, &(data->mc_reg_table));
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize MCRegTable for the MC register addresses!", return result;);

	result = tonga_convert_mc_reg_table_to_smc(hwmgr, &data->mc_reg_table);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize MCRegTable for driver state!", return result;);

	return tonga_copy_bytes_to_smc(hwmgr->smumgr, data->mc_reg_table_start,
			(uint8_t *)&data->mc_reg_table, sizeof(SMU72_Discrete_MCRegisters), data->sram_end);
}
