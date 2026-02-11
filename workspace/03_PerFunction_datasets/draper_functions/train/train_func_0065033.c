lirc_sir_init(void)
{
	int retval;

	retval = platform_driver_register(&lirc_sir_driver);
	if (retval) {
		pr_err("Platform driver register failed!\n");
		return -ENODEV;
	}

	lirc_sir_dev = platform_device_alloc("lirc_dev", 0);
	if (!lirc_sir_dev) {
		pr_err("Platform device alloc failed!\n");
		retval = -ENOMEM;
		goto pdev_alloc_fail;
	}

	retval = platform_device_add(lirc_sir_dev);
	if (retval) {
		pr_err("Platform device add failed!\n");
		retval = -ENODEV;
		goto pdev_add_fail;
	}

	retval = init_chrdev();
	if (retval < 0)
		goto fail;

	retval = init_lirc_sir();
	if (retval) {
		drop_chrdev();
		goto fail;
	}

	return 0;

fail:
	platform_device_del(lirc_sir_dev);
pdev_add_fail:
	platform_device_put(lirc_sir_dev);
pdev_alloc_fail:
	platform_driver_unregister(&lirc_sir_driver);
	return retval;
}
