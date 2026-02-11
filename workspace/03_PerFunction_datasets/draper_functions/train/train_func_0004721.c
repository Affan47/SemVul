mbus_dev_probe(struct device *d)
{
	int err;
	struct mbus_device *dev = dev_to_mbus(d);
	struct mbus_driver *drv = drv_to_mbus(dev->dev.driver);

	err = drv->probe(dev);
	if (!err)
		if (drv->scan)
			drv->scan(dev);
	return err;
}
