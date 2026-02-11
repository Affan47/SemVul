vc4_drm_register(void)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(component_drivers); i++) {
		ret = platform_driver_register(component_drivers[i]);
		if (ret) {
			while (--i >= 0)
				platform_driver_unregister(component_drivers[i]);
			return ret;
		}
	}
	return platform_driver_register(&vc4_platform_driver);
}
