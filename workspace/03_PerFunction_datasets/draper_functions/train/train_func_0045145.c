acpi_power_get_context(acpi_handle handle)
{
	struct acpi_device *device;

	if (acpi_bus_get_device(handle, &device))
		return NULL;

	return to_power_resource(device);
}
