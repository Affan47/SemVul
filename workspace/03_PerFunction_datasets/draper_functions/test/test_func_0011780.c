ath6kl_debug_init_fs(struct ath6kl *ar)
{
	ar->debugfs_phy = debugfs_create_dir("ath6kl",
					     ar->wiphy->debugfsdir);
	if (!ar->debugfs_phy)
		return -ENOMEM;

	debugfs_create_file("tgt_stats", S_IRUSR, ar->debugfs_phy, ar,
			    &fops_tgt_stats);

	if (ar->hif_type == ATH6KL_HIF_TYPE_SDIO)
		debugfs_create_file("credit_dist_stats", S_IRUSR,
				    ar->debugfs_phy, ar,
				    &fops_credit_dist_stats);

	debugfs_create_file("endpoint_stats", S_IRUSR | S_IWUSR,
			    ar->debugfs_phy, ar, &fops_endpoint_stats);

	debugfs_create_file("fwlog", S_IRUSR, ar->debugfs_phy, ar,
			    &fops_fwlog);

	debugfs_create_file("fwlog_block", S_IRUSR, ar->debugfs_phy, ar,
			    &fops_fwlog_block);

	debugfs_create_file("fwlog_mask", S_IRUSR | S_IWUSR, ar->debugfs_phy,
			    ar, &fops_fwlog_mask);

	debugfs_create_file("reg_addr", S_IRUSR | S_IWUSR, ar->debugfs_phy, ar,
			    &fops_diag_reg_read);

	debugfs_create_file("reg_dump", S_IRUSR, ar->debugfs_phy, ar,
			    &fops_reg_dump);

	debugfs_create_file("lrssi_roam_threshold", S_IRUSR | S_IWUSR,
			    ar->debugfs_phy, ar, &fops_lrssi_roam_threshold);

	debugfs_create_file("reg_write", S_IRUSR | S_IWUSR,
			    ar->debugfs_phy, ar, &fops_diag_reg_write);

	debugfs_create_file("war_stats", S_IRUSR, ar->debugfs_phy, ar,
			    &fops_war_stats);

	debugfs_create_file("roam_table", S_IRUSR, ar->debugfs_phy, ar,
			    &fops_roam_table);

	debugfs_create_file("force_roam", S_IWUSR, ar->debugfs_phy, ar,
			    &fops_force_roam);

	debugfs_create_file("roam_mode", S_IWUSR, ar->debugfs_phy, ar,
			    &fops_roam_mode);

	debugfs_create_file("keepalive", S_IRUSR | S_IWUSR, ar->debugfs_phy, ar,
			    &fops_keepalive);

	debugfs_create_file("disconnect_timeout", S_IRUSR | S_IWUSR,
			    ar->debugfs_phy, ar, &fops_disconnect_timeout);

	debugfs_create_file("create_qos", S_IWUSR, ar->debugfs_phy, ar,
			    &fops_create_qos);

	debugfs_create_file("delete_qos", S_IWUSR, ar->debugfs_phy, ar,
			    &fops_delete_qos);

	debugfs_create_file("bgscan_interval", S_IWUSR,
			    ar->debugfs_phy, ar, &fops_bgscan_int);

	debugfs_create_file("listen_interval", S_IRUSR | S_IWUSR,
			    ar->debugfs_phy, ar, &fops_listen_int);

	debugfs_create_file("power_params", S_IWUSR, ar->debugfs_phy, ar,
			    &fops_power_params);

	return 0;
}
