ipw_init(void)
{
	int ret;

	printk(KERN_INFO DRV_NAME ": " DRV_DESCRIPTION ", " DRV_VERSION "\n");
	printk(KERN_INFO DRV_NAME ": " DRV_COPYRIGHT "\n");

	ret = pci_register_driver(&ipw_driver);
	if (ret) {
		IPW_ERROR("Unable to initialize PCI module\n");
		return ret;
	}

	ret = driver_create_file(&ipw_driver.driver, &driver_attr_debug_level);
	if (ret) {
		IPW_ERROR("Unable to create driver sysfs file\n");
		pci_unregister_driver(&ipw_driver);
		return ret;
	}

	return ret;
}
