acpi_battery_is_charged(struct acpi_battery *battery)
{

	if (battery->state != 0)
		return 0;


	if (battery->capacity_now == ACPI_BATTERY_VALUE_UNKNOWN ||
	    battery->capacity_now == 0)
		return 0;


	if (battery->full_charge_capacity == battery->capacity_now)
		return 1;


	if (battery->design_capacity == battery->capacity_now)
		return 1;


	return 0;
}
