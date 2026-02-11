hisi_thermal_register_sensor(struct platform_device *pdev,
					struct hisi_thermal_data *data,
					struct hisi_thermal_sensor *sensor,
					int index)
{
	int ret, i;
	const struct thermal_trip *trip;

	sensor->id = index;
	sensor->thermal = data;

	sensor->tzd = thermal_zone_of_sensor_register(&pdev->dev, sensor->id,
				sensor, &hisi_of_thermal_ops);
	if (IS_ERR(sensor->tzd)) {
		ret = PTR_ERR(sensor->tzd);
		dev_err(&pdev->dev, "failed to register sensor id %d: %d\n",
			sensor->id, ret);
		return ret;
	}

	trip = of_thermal_get_trip_points(sensor->tzd);

	for (i = 0; i < of_thermal_get_ntrips(sensor->tzd); i++) {
		if (trip[i].type == THERMAL_TRIP_PASSIVE) {
			sensor->thres_temp = trip[i].temperature;
			break;
		}
	}

	return 0;
}
