rsxx_debugfs_dev_new(struct rsxx_cardinfo *card)
{
	struct dentry *debugfs_stats;
	struct dentry *debugfs_pci_regs;
	struct dentry *debugfs_cram;

	card->debugfs_dir = debugfs_create_dir(card->gendisk->disk_name, NULL);
	if (IS_ERR_OR_NULL(card->debugfs_dir))
		goto failed_debugfs_dir;

	debugfs_stats = debugfs_create_file("stats", S_IRUGO,
					    card->debugfs_dir, card,
					    &debugfs_stats_fops);
	if (IS_ERR_OR_NULL(debugfs_stats))
		goto failed_debugfs_stats;

	debugfs_pci_regs = debugfs_create_file("pci_regs", S_IRUGO,
					       card->debugfs_dir, card,
					       &debugfs_pci_regs_fops);
	if (IS_ERR_OR_NULL(debugfs_pci_regs))
		goto failed_debugfs_pci_regs;

	debugfs_cram = debugfs_create_file("cram", S_IRUGO | S_IWUSR,
					   card->debugfs_dir, card,
					   &debugfs_cram_fops);
	if (IS_ERR_OR_NULL(debugfs_cram))
		goto failed_debugfs_cram;

	return;
failed_debugfs_cram:
	debugfs_remove(debugfs_pci_regs);
failed_debugfs_pci_regs:
	debugfs_remove(debugfs_stats);
failed_debugfs_stats:
	debugfs_remove(card->debugfs_dir);
failed_debugfs_dir:
	card->debugfs_dir = NULL;
}
