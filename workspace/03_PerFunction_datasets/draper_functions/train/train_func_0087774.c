ti_thermal_set_mode(struct thermal_zone_device *thermal,
			       enum thermal_device_mode mode)
{
	struct ti_thermal_data *data = thermal->devdata;
	struct ti_bandgap *bgp;

	bgp = data->bgp;

	if (!data->ti_thermal) {
		dev_notice(&thermal->device, "thermal zone not registered\n");
		return 0;
	}

	mutex_lock(&data->ti_thermal->lock);

	if (mode == THERMAL_DEVICE_ENABLED)
		data->ti_thermal->polling_delay = FAST_TEMP_MONITORING_RATE;
	else
		data->ti_thermal->polling_delay = 0;

	mutex_unlock(&data->ti_thermal->lock);

	data->mode = mode;
	ti_bandgap_write_update_interval(bgp, data->sensor_id,
					data->ti_thermal->polling_delay);
	thermal_zone_device_update(data->ti_thermal);
	dev_dbg(&thermal->device, "thermal polling set for duration=%d msec\n",
		data->ti_thermal->polling_delay);

	return 0;
}
