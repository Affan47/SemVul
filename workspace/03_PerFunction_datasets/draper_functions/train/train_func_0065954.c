cros_ec_lpc_init(void)
{
	int ret;

	if (!dmi_check_system(cros_ec_lpc_dmi_table)) {
		pr_err(DRV_NAME ": unsupported system.\n");
		return -ENODEV;
	}


	ret = platform_driver_register(&cros_ec_lpc_driver);
	if (ret) {
		pr_err(DRV_NAME ": can't register driver: %d\n", ret);
		return ret;
	}


	ret = platform_device_register(&cros_ec_lpc_device);
	if (ret) {
		pr_err(DRV_NAME ": can't register device: %d\n", ret);
		platform_driver_unregister(&cros_ec_lpc_driver);
		return ret;
	}

	return 0;
}
