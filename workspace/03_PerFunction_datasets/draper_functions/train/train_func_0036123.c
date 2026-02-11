cciss_create_ld_sysfs_entry(struct ctlr_info *h,
				       int drv_index)
{
	struct device *dev;

	if (h->drv[drv_index]->device_initialized)
		return 0;

	dev = &h->drv[drv_index]->dev;
	device_initialize(dev);
	dev->type = &cciss_dev_type;
	dev->bus = &cciss_bus_type;
	dev_set_name(dev, "c%dd%d", h->ctlr, drv_index);
	dev->parent = &h->dev;
	h->drv[drv_index]->device_initialized = 1;
	return device_add(dev);
}
