print_basics(struct powernow_k8_data *data)
{
	int j;
	for (j = 0; j < data->numps; j++) {
		if (data->powernow_table[j].frequency !=
				CPUFREQ_ENTRY_INVALID) {
			pr_info("fid 0x%x (%d MHz), vid 0x%x\n",
				data->powernow_table[j].driver_data & 0xff,
				data->powernow_table[j].frequency/1000,
				data->powernow_table[j].driver_data >> 8);
		}
	}
	if (data->batps)
		pr_info("Only %d pstates on battery\n", data->batps);
}
