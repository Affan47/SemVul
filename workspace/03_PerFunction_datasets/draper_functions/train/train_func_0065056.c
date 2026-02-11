pvpanic_add(struct acpi_device *device)
{
	int ret;

	ret = acpi_bus_get_status(device);
	if (ret < 0)
		return ret;

	if (!device->status.enabled || !device->status.functional)
		return -ENODEV;

	acpi_walk_resources(device->handle, METHOD_NAME__CRS,
			    pvpanic_walk_resources, NULL);

	if (!port)
		return -ENODEV;

	atomic_notifier_chain_register(&panic_notifier_list,
				       &pvpanic_panic_nb);

	return 0;
}
