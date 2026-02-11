usbip_status_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct stub_device *sdev = dev_get_drvdata(dev);
	int status;

	if (!sdev) {
		dev_err(dev, "sdev is null\n");
		return -ENODEV;
	}

	spin_lock_irq(&sdev->ud.lock);
	status = sdev->ud.status;
	spin_unlock_irq(&sdev->ud.lock);

	return snprintf(buf, PAGE_SIZE, "%d\n", status);
}
