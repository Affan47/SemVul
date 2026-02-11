sys_set_trip_temp(struct thermal_zone_device *tzd, int trip,
			     int temp)
{
	struct intel_soc_dts_sensor_entry *dts = tzd->devdata;
	struct intel_soc_dts_sensors *sensors = dts->sensors;
	int status;

	if (temp > sensors->tj_max)
		return -EINVAL;

	mutex_lock(&sensors->dts_update_lock);
	status = update_trip_temp(tzd->devdata, trip, temp,
				  dts->trip_types[trip]);
	mutex_unlock(&sensors->dts_update_lock);

	return status;
}
