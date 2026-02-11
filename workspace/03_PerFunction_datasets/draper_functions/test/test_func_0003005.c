abituguru_init(void)
{
	int address, err;
	struct resource res = { .flags = IORESOURCE_IO };
	const char *board_vendor = dmi_get_system_info(DMI_BOARD_VENDOR);


	if (!force && (!board_vendor ||
			strcmp(board_vendor, "http://www.abit.com.tw/")))
		return -ENODEV;

	address = abituguru_detect();
	if (address < 0)
		return address;

	err = platform_driver_register(&abituguru_driver);
	if (err)
		goto exit;

	abituguru_pdev = platform_device_alloc(ABIT_UGURU_NAME, address);
	if (!abituguru_pdev) {
		pr_err("Device allocation failed\n");
		err = -ENOMEM;
		goto exit_driver_unregister;
	}

	res.start = address;
	res.end = address + ABIT_UGURU_REGION_LENGTH - 1;
	res.name = ABIT_UGURU_NAME;

	err = platform_device_add_resources(abituguru_pdev, &res, 1);
	if (err) {
		pr_err("Device resource addition failed (%d)\n", err);
		goto exit_device_put;
	}

	err = platform_device_add(abituguru_pdev);
	if (err) {
		pr_err("Device addition failed (%d)\n", err);
		goto exit_device_put;
	}

	return 0;

exit_device_put:
	platform_device_put(abituguru_pdev);
exit_driver_unregister:
	platform_driver_unregister(&abituguru_driver);
exit:
	return err;
}
