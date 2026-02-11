of_thermal_get_crit_temp(struct thermal_zone_device *tz,
				    int *temp)
{
	struct __thermal_zone *data = tz->devdata;
	int i;

	for (i = 0; i < data->ntrips; i++)
		if (data->trips[i].type == THERMAL_TRIP_CRITICAL) {
			*temp = data->trips[i].temperature;
			return 0;
		}

	return -EINVAL;
}
