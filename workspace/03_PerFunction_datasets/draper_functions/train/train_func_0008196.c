f7188x_gpio_device_add(const struct f7188x_sio *sio)
{
	int err;

	f7188x_gpio_pdev = platform_device_alloc(DRVNAME, -1);
	if (!f7188x_gpio_pdev)
		return -ENOMEM;

	err = platform_device_add_data(f7188x_gpio_pdev,
				       sio, sizeof(*sio));
	if (err) {
		pr_err(DRVNAME "Platform data allocation failed\n");
		goto err;
	}

	err = platform_device_add(f7188x_gpio_pdev);
	if (err) {
		pr_err(DRVNAME "Device addition failed\n");
		goto err;
	}

	return 0;

err:
	platform_device_put(f7188x_gpio_pdev);

	return err;
}
