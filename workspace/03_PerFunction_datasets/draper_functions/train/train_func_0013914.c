ti_thermal_remove_sensor(struct ti_bandgap *bgp, int id)
{
	struct ti_thermal_data *data;

	data = ti_bandgap_get_sensor_data(bgp, id);

	if (data && data->ti_thermal) {
		if (data->our_zone)
			thermal_zone_device_unregister(data->ti_thermal);
		else
			thermal_zone_of_sensor_unregister(bgp->dev,
							  data->ti_thermal);
	}

	return 0;
}
