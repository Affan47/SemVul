sch311x_gpio_init(void)
{
	int err, i;
	unsigned short addr = 0;

	for (i = 0; i < ARRAY_SIZE(sch311x_ioports); i++)
		if (sch311x_detect(sch311x_ioports[i], &addr) == 0)
			break;

	if (!addr)
		return -ENODEV;

	err = platform_driver_register(&sch311x_gpio_driver);
	if (err)
		return err;

	err = sch311x_gpio_pdev_add(addr);
	if (err)
		goto unreg_platform_driver;

	return 0;

unreg_platform_driver:
	platform_driver_unregister(&sch311x_gpio_driver);
	return err;
}
