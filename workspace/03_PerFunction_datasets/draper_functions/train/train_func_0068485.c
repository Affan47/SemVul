ena_com_update_nonadaptive_moderation_interval_tx(struct ena_com_dev *ena_dev,
						      u32 tx_coalesce_usecs)
{
	if (!ena_dev->intr_delay_resolution) {
		pr_err("Illegal interrupt delay granularity value\n");
		return -EFAULT;
	}

	ena_dev->intr_moder_tx_interval = tx_coalesce_usecs /
		ena_dev->intr_delay_resolution;

	return 0;
}
