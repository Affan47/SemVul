ath10k_wmi_fw_stats_num_peers(struct list_head *head)
{
	struct ath10k_fw_stats_peer *i;
	size_t num = 0;

	list_for_each_entry(i, head, list)
		++num;

	return num;
}
