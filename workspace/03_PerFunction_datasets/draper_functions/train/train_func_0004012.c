acpi_power_meter_add(struct acpi_device *device)
{
	int res;
	struct acpi_power_meter_resource *resource;

	if (!device)
		return -EINVAL;

	resource = kzalloc(sizeof(struct acpi_power_meter_resource),
			   GFP_KERNEL);
	if (!resource)
		return -ENOMEM;

	resource->sensors_valid = 0;
	resource->acpi_dev = device;
	mutex_init(&resource->lock);
	strcpy(acpi_device_name(device), ACPI_POWER_METER_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_POWER_METER_CLASS);
	device->driver_data = resource;

	free_capabilities(resource);
	res = read_capabilities(resource);
	if (res)
		goto exit_free;

	resource->trip[0] = resource->trip[1] = -1;

	res = setup_attrs(resource);
	if (res)
		goto exit_free;

	resource->hwmon_dev = hwmon_device_register(&device->dev);
	if (IS_ERR(resource->hwmon_dev)) {
		res = PTR_ERR(resource->hwmon_dev);
		goto exit_remove;
	}

	res = 0;
	goto exit;

exit_remove:
	remove_attrs(resource);
exit_free:
	kfree(resource);
exit:
	return res;
}
