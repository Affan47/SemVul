sumo_construct_sclk_voltage_mapping_table(struct amdgpu_device *adev,
						      struct sumo_sclk_voltage_mapping_table *sclk_voltage_mapping_table,
						      ATOM_AVAILABLE_SCLK_LIST *table)
{
	u32 i;
	u32 n = 0;
	u32 prev_sclk = 0;

	for (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++) {
		if (table[i].ulSupportedSCLK > prev_sclk) {
			sclk_voltage_mapping_table->entries[n].sclk_frequency =
				table[i].ulSupportedSCLK;
			sclk_voltage_mapping_table->entries[n].vid_2bit =
				table[i].usVoltageIndex;
			prev_sclk = table[i].ulSupportedSCLK;
			n++;
		}
	}

	sclk_voltage_mapping_table->num_max_dpm_entries = n;
}
