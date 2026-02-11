setup_debugfs(struct c4iw_dev *devp)
{
	if (!devp->debugfs_root)
		return -1;

	debugfs_create_file_size("qps", S_IWUSR, devp->debugfs_root,
				 (void *)devp, &qp_debugfs_fops, 4096);

	debugfs_create_file_size("stags", S_IWUSR, devp->debugfs_root,
				 (void *)devp, &stag_debugfs_fops, 4096);

	debugfs_create_file_size("stats", S_IWUSR, devp->debugfs_root,
				 (void *)devp, &stats_debugfs_fops, 4096);

	debugfs_create_file_size("eps", S_IWUSR, devp->debugfs_root,
				 (void *)devp, &ep_debugfs_fops, 4096);

	if (c4iw_wr_log)
		debugfs_create_file_size("wr_log", S_IWUSR, devp->debugfs_root,
					 (void *)devp, &wr_log_debugfs_fops, 4096);
	return 0;
}
