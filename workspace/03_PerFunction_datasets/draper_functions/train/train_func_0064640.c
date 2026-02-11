acpi_thermal_guess_offset(struct acpi_thermal *tz)
{
	if (tz->trips.critical.flags.valid &&
	    (tz->trips.critical.temperature % 5) == 1)
		tz->kelvin_offset = 2731;
	else
		tz->kelvin_offset = 2732;
}
