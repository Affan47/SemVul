il4965_init(void)
{

	int ret;
	pr_info(DRV_DESCRIPTION ", " DRV_VERSION "\n");
	pr_info(DRV_COPYRIGHT "\n");

	ret = il4965_rate_control_register();
	if (ret) {
		pr_err("Unable to register rate control algorithm: %d\n", ret);
		return ret;
	}

	ret = pci_register_driver(&il4965_driver);
	if (ret) {
		pr_err("Unable to initialize PCI module\n");
		goto error_register;
	}

	return ret;

error_register:
	il4965_rate_control_unregister();
	return ret;
}
