dw_spi_debugfs_init(struct dw_spi *dws)
{
	char name[128];

	snprintf(name, 128, "dw_spi-%s", dev_name(&dws->master->dev));
	dws->debugfs = debugfs_create_dir(name, NULL);
	if (!dws->debugfs)
		return -ENOMEM;

	debugfs_create_file("registers", S_IFREG | S_IRUGO,
		dws->debugfs, (void *)dws, &dw_spi_regs_ops);
	return 0;
}
