tpacpi_brightness_set_ec(unsigned int value)
{
	u8 lec = 0;

	if (unlikely(!acpi_ec_read(TP_EC_BACKLIGHT, &lec)))
		return -EIO;

	if (unlikely(!acpi_ec_write(TP_EC_BACKLIGHT,
				(lec & TP_EC_BACKLIGHT_CMDMSK) |
				(value & TP_EC_BACKLIGHT_LVLMSK))))
		return -EIO;

	return 0;
}
