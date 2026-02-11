get_uvd_clock_voltage_limit_table(struct pp_hwmgr *hwmgr,
		struct phm_uvd_clock_voltage_dependency_table **ptable,
		const ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *table,
		const UVDClockInfoArray *array)
{
	unsigned long table_size, i;
	struct phm_uvd_clock_voltage_dependency_table *uvd_table;

	table_size = sizeof(unsigned long) +
		 sizeof(struct phm_uvd_clock_voltage_dependency_table) *
		 table->numEntries;

	uvd_table = kzalloc(table_size, GFP_KERNEL);
	if (NULL == uvd_table)
		return -ENOMEM;

	uvd_table->count = table->numEntries;

	for (i = 0; i < table->numEntries; i++) {
		const UVDClockInfo *entry =
			&array->entries[table->entries[i].ucUVDClockInfoIndex];
		uvd_table->entries[i].v = (unsigned long)le16_to_cpu(table->entries[i].usVoltage);
		uvd_table->entries[i].vclk = ((unsigned long)entry->ucVClkHigh << 16)
					 | le16_to_cpu(entry->usVClkLow);
		uvd_table->entries[i].dclk = ((unsigned long)entry->ucDClkHigh << 16)
					 | le16_to_cpu(entry->usDClkLow);
	}

	*ptable = uvd_table;

	return 0;
}
