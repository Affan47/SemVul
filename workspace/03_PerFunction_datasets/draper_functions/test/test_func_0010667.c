cxgb4vf_module_init(void)
{
	int ret;


	if (msi != MSI_MSIX && msi != MSI_MSI) {
		pr_warn("bad module parameter msi=%d; must be %d (MSI-X or MSI) or %d (MSI)\n",
			msi, MSI_MSIX, MSI_MSI);
		return -EINVAL;
	}


	cxgb4vf_debugfs_root = debugfs_create_dir(KBUILD_MODNAME, NULL);
	if (IS_ERR_OR_NULL(cxgb4vf_debugfs_root))
		pr_warn("could not create debugfs entry, continuing\n");

	ret = pci_register_driver(&cxgb4vf_driver);
	if (ret < 0 && !IS_ERR_OR_NULL(cxgb4vf_debugfs_root))
		debugfs_remove(cxgb4vf_debugfs_root);
	return ret;
}
