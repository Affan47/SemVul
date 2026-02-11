thermal_get_crit_temp(struct thermal_zone_device *thermal,
				int *temperature)
{
	struct acpi_thermal *tz = thermal->devdata;

	if (tz->trips.critical.flags.valid) {
		*temperature = DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET(
				tz->trips.critical.temperature,
				tz->kelvin_offset);
		return 0;
	} else
		return -EINVAL;
}
