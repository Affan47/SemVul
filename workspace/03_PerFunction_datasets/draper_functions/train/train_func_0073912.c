ssb_device_get(struct ssb_device *dev)
{
	if (dev)
		get_device(dev->dev);
	return dev;
}
