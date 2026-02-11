mic_x100_dma_init(void)
{
	int rc = mbus_register_driver(&mic_dma_driver);
	if (rc)
		return rc;
	mic_dma_dbg = debugfs_create_dir(KBUILD_MODNAME, NULL);
	return 0;
}
