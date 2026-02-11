sony_backlight_get_brightness(struct backlight_device *bd)
{
	int value;

	if (sony_nc_int_call(sony_nc_acpi_handle, "GBRT", NULL, &value))
		return 0;

	return value - 1;
}
