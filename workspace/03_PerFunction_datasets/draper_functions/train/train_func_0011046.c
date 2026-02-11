devm_snd_soc_register_platform(struct device *dev,
			const struct snd_soc_platform_driver *platform_drv)
{
	struct device **ptr;
	int ret;

	ptr = devres_alloc(devm_platform_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = snd_soc_register_platform(dev, platform_drv);
	if (ret == 0) {
		*ptr = dev;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return ret;
}
