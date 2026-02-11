vfb_init(void)
{
	int ret = 0;

#ifndef MODULE
	char *option = NULL;

	if (fb_get_options("vfb", &option))
		return -ENODEV;
	vfb_setup(option);
#endif

	if (!vfb_enable)
		return -ENXIO;

	ret = platform_driver_register(&vfb_driver);

	if (!ret) {
		vfb_device = platform_device_alloc("vfb", 0);

		if (vfb_device)
			ret = platform_device_add(vfb_device);
		else
			ret = -ENOMEM;

		if (ret) {
			platform_device_put(vfb_device);
			platform_driver_unregister(&vfb_driver);
		}
	}

	return ret;
}
