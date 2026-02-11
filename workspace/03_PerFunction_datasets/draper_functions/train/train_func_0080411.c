acerhdf_get_trip_type(struct thermal_zone_device *thermal, int trip,
				 enum thermal_trip_type *type)
{
	if (trip == 0)
		*type = THERMAL_TRIP_ACTIVE;
	else if (trip == 1)
		*type = THERMAL_TRIP_CRITICAL;
	else
		return -EINVAL;

	return 0;
}
