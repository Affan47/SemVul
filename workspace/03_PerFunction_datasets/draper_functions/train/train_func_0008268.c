ci_convert_mc_reg_table_entry_to_smc(struct amdgpu_device *adev,
						 const u32 memory_clock,
						 SMU7_Discrete_MCRegisterSet *mc_reg_table_data)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	u32 i = 0;

	for(i = 0; i < pi->mc_reg_table.num_entries; i++) {
		if (memory_clock <= pi->mc_reg_table.mc_reg_table_entry[i].mclk_max)
			break;
	}

	if ((i == pi->mc_reg_table.num_entries) && (i > 0))
		--i;

	ci_convert_mc_registers(&pi->mc_reg_table.mc_reg_table_entry[i],
				mc_reg_table_data, pi->mc_reg_table.last,
				pi->mc_reg_table.valid_flag);
}
