ath10k_pci_fw_crashed_dump(struct ath10k *ar)
{
	struct ath10k_fw_crash_data *crash_data;
	char uuid[50];

	spin_lock_bh(&ar->data_lock);

	ar->stats.fw_crash_counter++;

	crash_data = ath10k_debug_get_new_fw_crash_data(ar);

	if (crash_data)
		scnprintf(uuid, sizeof(uuid), "%pUl", &crash_data->uuid);
	else
		scnprintf(uuid, sizeof(uuid), "n/a");

	ath10k_err(ar, "firmware crashed! (uuid %s)\n", uuid);
	ath10k_print_driver_info(ar);
	ath10k_pci_dump_registers(ar, crash_data);

	spin_unlock_bh(&ar->data_lock);

	queue_work(ar->workqueue, &ar->restart_work);
}
