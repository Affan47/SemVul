f7188x_gpio_init(void)
{
	int err;
	struct f7188x_sio sio;

	if (f7188x_find(0x2e, &sio) &&
	    f7188x_find(0x4e, &sio))
		return -ENODEV;

	err = platform_driver_register(&f7188x_gpio_driver);
	if (!err) {
		err = f7188x_gpio_device_add(&sio);
		if (err)
			platform_driver_unregister(&f7188x_gpio_driver);
	}

	return err;
}
