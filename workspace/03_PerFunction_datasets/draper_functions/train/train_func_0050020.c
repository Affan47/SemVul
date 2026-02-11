device_reprobe(struct device *dev)
{
	if (dev->driver) {
		if (dev->parent)
			device_lock(dev->parent);
		device_release_driver(dev);
		if (dev->parent)
			device_unlock(dev->parent);
	}
	return bus_rescan_devices_helper(dev, NULL);
}
