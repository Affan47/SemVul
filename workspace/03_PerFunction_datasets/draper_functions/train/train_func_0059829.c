thermal_get_temp(struct thermal_zone_device *thermal, int *temp)
{
	struct acpi_thermal *tz = thermal->devdata;
	int result;

	if (!tz)
		return -EINVAL;

	result = acpi_thermal_get_temperature(tz);
	if (result)
		return result;

	*temp = DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET(tz->temperature,
							tz->kelvin_offset);
	return 0;
}
