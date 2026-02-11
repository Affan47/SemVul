ulpi_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct ulpi *ulpi = to_ulpi_dev(dev);

	if (add_uevent_var(env, "MODALIAS=ulpi:v%04xp%04x",
			   ulpi->id.vendor, ulpi->id.product))
		return -ENOMEM;
	return 0;
}
