acpi_battery_refresh(struct acpi_battery *battery)
{
	int power_unit;

	if (!battery->bat)
		return;

	power_unit = battery->power_unit;

	acpi_battery_get_info(battery);

	if (power_unit == battery->power_unit)
		return;


	sysfs_remove_battery(battery);
	sysfs_add_battery(battery);
}
