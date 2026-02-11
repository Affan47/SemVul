lirc_serial_init(void)
{
	int result;


	result = lirc_buffer_init(&rbuf, sizeof(int), RBUF_LEN);
	if (result < 0)
		return result;

	result = platform_driver_register(&lirc_serial_driver);
	if (result) {
		printk("lirc register returned %d\n", result);
		goto exit_buffer_free;
	}

	lirc_serial_dev = platform_device_alloc("lirc_serial", 0);
	if (!lirc_serial_dev) {
		result = -ENOMEM;
		goto exit_driver_unregister;
	}

	result = platform_device_add(lirc_serial_dev);
	if (result)
		goto exit_device_put;

	return 0;

exit_device_put:
	platform_device_put(lirc_serial_dev);
exit_driver_unregister:
	platform_driver_unregister(&lirc_serial_driver);
exit_buffer_free:
	lirc_buffer_free(&rbuf);
	return result;
}
