fiji_complete_dependency_tables(struct pp_hwmgr *hwmgr)
{
	int result = 0;
	int tmp_result;
	struct fiji_hwmgr *data = (struct fiji_hwmgr *)(hwmgr->backend);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);

	tmp_result = fiji_patch_lookup_table_with_leakage(hwmgr,
			table_info->vddc_lookup_table, &(data->vddc_leakage));
	if (tmp_result)
		result = tmp_result;

	tmp_result = fiji_patch_clock_voltage_limits_with_vddc_leakage(hwmgr,
			&(data->vddc_leakage), &table_info->max_clock_voltage_on_dc.vddc);
	if (tmp_result)
		result = tmp_result;

	tmp_result = fiji_patch_voltage_dependency_tables_with_lookup_table(hwmgr);
	if (tmp_result)
		result = tmp_result;

	tmp_result = fiji_calc_voltage_dependency_tables(hwmgr);
	if (tmp_result)
		result = tmp_result;

	tmp_result = fiji_calc_mm_voltage_dependency_table(hwmgr);
	if (tmp_result)
		result = tmp_result;

	tmp_result = fiji_sort_lookup_table(hwmgr, table_info->vddc_lookup_table);
	if(tmp_result)
		result = tmp_result;

	return result;
}
