b43_sysfs_register(struct b43_wldev *wldev)
{
	struct device *dev = wldev->dev->dev;

	B43_WARN_ON(b43_status(wldev) != B43_STAT_INITIALIZED);

	return device_create_file(dev, &dev_attr_interference);
}
