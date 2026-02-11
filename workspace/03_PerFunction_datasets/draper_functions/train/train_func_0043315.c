acpi_bus_update_power(acpi_handle handle, int *state_p)
{
	struct acpi_device *device;
	int result;

	result = acpi_bus_get_device(handle, &device);
	return result ? result : acpi_device_update_power(device, state_p);
}
