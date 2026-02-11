cmpc_bl_get_brightness(struct backlight_device *bd)
{
	acpi_status status;
	acpi_handle handle;
	unsigned long long brightness;

	handle = bl_get_data(bd);
	status = cmpc_get_brightness(handle, &brightness);
	if (ACPI_SUCCESS(status))
		return brightness;
	else
		return -1;
}
