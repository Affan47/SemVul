drm_platform_init(struct drm_driver *driver, struct platform_device *platform_device)
{
	DRM_DEBUG("\n");

	return drm_get_platform_dev(platform_device, driver);
}
