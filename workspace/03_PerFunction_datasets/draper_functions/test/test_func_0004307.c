amd_ntb_pci_driver_init(void)
{
	pr_info("%s %s\n", NTB_DESC, NTB_VER);

	if (debugfs_initialized())
		debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, NULL);

	return pci_register_driver(&amd_ntb_pci_driver);
}
