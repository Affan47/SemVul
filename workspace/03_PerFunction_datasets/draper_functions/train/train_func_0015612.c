get_vce_clock_voltage_limit_table_size(struct pp_hwmgr *hwmgr,
							const ATOM_PPLIB_POWERPLAYTABLE *powerplay_table)
{
	uint16_t table_offset = get_vce_clock_voltage_limit_table_offset(hwmgr, powerplay_table);
	uint16_t table_size = 0;

	if (table_offset > 0) {
		const ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *ptable =
			(const ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *)(((unsigned long) powerplay_table) + table_offset);

		table_size = sizeof(uint8_t) + ptable->numEntries * sizeof(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record);
	}
	return table_size;
}
