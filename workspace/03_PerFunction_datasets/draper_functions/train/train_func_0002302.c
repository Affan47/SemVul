child_unregister(struct device *dev, void *data)
{


	if (dev->class)
		;
	else
		nd_device_unregister(dev, ND_SYNC);
	return 0;
}
