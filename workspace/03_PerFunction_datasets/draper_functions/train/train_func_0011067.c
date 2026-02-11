__mmc_test_register_dbgfs_file(struct mmc_card *card,
	const char *name, umode_t mode, const struct file_operations *fops)
{
	struct dentry *file = NULL;
	struct mmc_test_dbgfs_file *df;

	if (card->debugfs_root)
		file = debugfs_create_file(name, mode, card->debugfs_root,
			card, fops);

	if (IS_ERR_OR_NULL(file)) {
		dev_err(&card->dev,
			"Can't create %s. Perhaps debugfs is disabled.\n",
			name);
		return -ENODEV;
	}

	df = kmalloc(sizeof(struct mmc_test_dbgfs_file), GFP_KERNEL);
	if (!df) {
		debugfs_remove(file);
		dev_err(&card->dev,
			"Can't allocate memory for internal usage.\n");
		return -ENOMEM;
	}

	df->card = card;
	df->file = file;

	list_add(&df->link, &mmc_test_file_test);
	return 0;
}
