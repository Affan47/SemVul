of_thermal_is_trip_valid(struct thermal_zone_device *tz, int trip)
{
	struct __thermal_zone *data = tz->devdata;

	if (!data || trip >= data->ntrips || trip < 0)
		return false;

	return true;
}
