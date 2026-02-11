acpi_scan_try_to_offline(struct acpi_device *device)
{
	acpi_handle handle = device->handle;
	struct device *errdev = NULL;
	acpi_status status;


	status = acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				     NULL, acpi_bus_offline, (void *)false,
				     (void **)&errdev);
	if (status == AE_SUPPORT) {
		dev_warn(errdev, "Offline disabled.\n");
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    acpi_bus_online, NULL, NULL, NULL);
		return -EPERM;
	}
	acpi_bus_offline(handle, 0, (void *)false, (void **)&errdev);
	if (errdev) {
		errdev = NULL;
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    NULL, acpi_bus_offline, (void *)true,
				    (void **)&errdev);
		if (!errdev || acpi_force_hot_remove)
			acpi_bus_offline(handle, 0, (void *)true,
					 (void **)&errdev);

		if (errdev && !acpi_force_hot_remove) {
			dev_warn(errdev, "Offline failed.\n");
			acpi_bus_online(handle, 0, NULL, NULL);
			acpi_walk_namespace(ACPI_TYPE_ANY, handle,
					    ACPI_UINT32_MAX, acpi_bus_online,
					    NULL, NULL, NULL);
			return -EBUSY;
		}
	}
	return 0;
}
