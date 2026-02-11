__device_release_driver(struct device *dev)
{
	struct device_driver *drv;

	drv = dev->driver;
	if (drv) {
		if (driver_allows_async_probing(drv))
			async_synchronize_full();

		pm_runtime_get_sync(dev);

		driver_sysfs_remove(dev);

		if (dev->bus)
			blocking_notifier_call_chain(&dev->bus->p->bus_notifier,
						     BUS_NOTIFY_UNBIND_DRIVER,
						     dev);

		pm_runtime_put_sync(dev);

		if (dev->bus && dev->bus->remove)
			dev->bus->remove(dev);
		else if (drv->remove)
			drv->remove(dev);
		devres_release_all(dev);
		dev->driver = NULL;
		dev_set_drvdata(dev, NULL);
		if (dev->pm_domain && dev->pm_domain->dismiss)
			dev->pm_domain->dismiss(dev);

		klist_remove(&dev->p->knode_driver);
		if (dev->bus)
			blocking_notifier_call_chain(&dev->bus->p->bus_notifier,
						     BUS_NOTIFY_UNBOUND_DRIVER,
						     dev);

	}
}
