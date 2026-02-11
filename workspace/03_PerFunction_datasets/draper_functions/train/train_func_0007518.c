container_device_attach(struct acpi_device *adev,
				   const struct acpi_device_id *not_used)
{
	struct container_dev *cdev;
	struct device *dev;
	int ret;

	if (adev->flags.is_dock_station)
		return 0;

	cdev = kzalloc(sizeof(*cdev), GFP_KERNEL);
	if (!cdev)
		return -ENOMEM;

	cdev->offline = acpi_container_offline;
	dev = &cdev->dev;
	dev->bus = &container_subsys;
	dev_set_name(dev, "%s", dev_name(&adev->dev));
	ACPI_COMPANION_SET(dev, adev);
	dev->release = acpi_container_release;
	ret = device_register(dev);
	if (ret) {
		put_device(dev);
		return ret;
	}
	adev->driver_data = dev;
	return 1;
}
