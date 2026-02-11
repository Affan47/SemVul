acpi_video_bus_match(acpi_handle handle, u32 level, void *context,
			void **return_value)
{
	struct acpi_device *device = context;
	struct acpi_device *sibling;
	int result;

	if (handle == device->handle)
		return AE_CTRL_TERMINATE;

	result = acpi_bus_get_device(handle, &sibling);
	if (result)
		return AE_OK;

	if (!strcmp(acpi_device_name(sibling), ACPI_VIDEO_BUS_NAME))
			return AE_ALREADY_EXISTS;

	return AE_OK;
}
