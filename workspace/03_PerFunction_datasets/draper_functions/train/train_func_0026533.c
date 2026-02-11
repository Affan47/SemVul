lbs_fw_index_to_data_rate(u8 idx)
{
	if (idx >= sizeof(fw_data_rates))
		idx = 0;
	return fw_data_rates[idx];
}
