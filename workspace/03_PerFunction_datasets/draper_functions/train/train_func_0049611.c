si_initialize_smc_dte_tables(struct radeon_device *rdev)
{
	struct si_power_info *si_pi = si_get_pi(rdev);
	int ret = 0;
	struct si_dte_data *dte_data = &si_pi->dte_data;
	Smc_SIslands_DTE_Configuration *dte_tables = NULL;
	u32 table_size;
	u8 tdep_count;
	u32 i;

	if (dte_data == NULL)
		si_pi->enable_dte = false;

	if (si_pi->enable_dte == false)
		return 0;

	if (dte_data->k <= 0)
		return -EINVAL;

	dte_tables = kzalloc(sizeof(Smc_SIslands_DTE_Configuration), GFP_KERNEL);
	if (dte_tables == NULL) {
		si_pi->enable_dte = false;
		return -ENOMEM;
	}

	table_size = dte_data->k;

	if (table_size > SMC_SISLANDS_DTE_MAX_FILTER_STAGES)
		table_size = SMC_SISLANDS_DTE_MAX_FILTER_STAGES;

	tdep_count = dte_data->tdep_count;
	if (tdep_count > SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE)
		tdep_count = SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE;

	dte_tables->K = cpu_to_be32(table_size);
	dte_tables->T0 = cpu_to_be32(dte_data->t0);
	dte_tables->MaxT = cpu_to_be32(dte_data->max_t);
	dte_tables->WindowSize = dte_data->window_size;
	dte_tables->temp_select = dte_data->temp_select;
	dte_tables->DTE_mode = dte_data->dte_mode;
	dte_tables->Tthreshold = cpu_to_be32(dte_data->t_threshold);

	if (tdep_count > 0)
		table_size--;

	for (i = 0; i < table_size; i++) {
		dte_tables->tau[i] = cpu_to_be32(dte_data->tau[i]);
		dte_tables->R[i]   = cpu_to_be32(dte_data->r[i]);
	}

	dte_tables->Tdep_count = tdep_count;

	for (i = 0; i < (u32)tdep_count; i++) {
		dte_tables->T_limits[i] = dte_data->t_limits[i];
		dte_tables->Tdep_tau[i] = cpu_to_be32(dte_data->tdep_tau[i]);
		dte_tables->Tdep_R[i] = cpu_to_be32(dte_data->tdep_r[i]);
	}

	ret = si_copy_bytes_to_smc(rdev, si_pi->dte_table_start, (u8 *)dte_tables,
				   sizeof(Smc_SIslands_DTE_Configuration), si_pi->sram_end);
	kfree(dte_tables);

	return ret;
}
