driver_probe_device(struct device_driver *drv, struct device *dev)
{
	int ret = 0;

	if (!device_is_registered(dev))
		return -ENODEV;

	pr_debug("bus: '%s': %s: matched device %s with driver %s\n",
		 drv->bus->name, __func__, dev_name(dev), drv->name);

	if (dev->parent)
		pm_runtime_get_sync(dev->parent);

	pm_runtime_barrier(dev);
	ret = really_probe(dev, drv);
	pm_request_idle(dev);

	if (dev->parent)
		pm_runtime_put(dev->parent);

	return ret;
}
