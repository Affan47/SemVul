typename_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct visor_device *vdev = to_visor_device(dev);
	int i = 0;
	struct bus_type *xbus = dev->bus;
	struct device_driver *xdrv = dev->driver;
	struct visor_driver *drv = NULL;

	if (!vdev->visorchannel || !xbus || !xdrv)
		return 0;
	i = xbus->match(dev, xdrv);
	if (!i)
		return 0;
	drv = to_visor_driver(xdrv);
	return snprintf(buf, PAGE_SIZE, "%s\n", drv->channel_types[i - 1].name);
}
