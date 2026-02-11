imx_get_temp(struct thermal_zone_device *tz, int *temp)
{
	struct imx_thermal_data *data = tz->devdata;
	struct regmap *map = data->tempmon;
	unsigned int n_meas;
	bool wait;
	u32 val;

	if (data->mode == THERMAL_DEVICE_ENABLED) {

		regmap_read(map, TEMPSENSE0, &val);
		wait = !(val & TEMPSENSE0_FINISHED);
	} else {


		regmap_write(map, TEMPSENSE0 + REG_CLR, TEMPSENSE0_POWER_DOWN);
		regmap_write(map, TEMPSENSE0 + REG_SET, TEMPSENSE0_MEASURE_TEMP);

		wait = true;
	}


	if (wait)
		usleep_range(20, 50);

	regmap_read(map, TEMPSENSE0, &val);

	if (data->mode != THERMAL_DEVICE_ENABLED) {
		regmap_write(map, TEMPSENSE0 + REG_CLR, TEMPSENSE0_MEASURE_TEMP);
		regmap_write(map, TEMPSENSE0 + REG_SET, TEMPSENSE0_POWER_DOWN);
	}

	if ((val & TEMPSENSE0_FINISHED) == 0) {
		dev_dbg(&tz->device, "temp measurement never finished\n");
		return -EAGAIN;
	}

	n_meas = (val & TEMPSENSE0_TEMP_CNT_MASK) >> TEMPSENSE0_TEMP_CNT_SHIFT;


	*temp = data->c2 - n_meas * data->c1;


	if (data->socdata->version == TEMPMON_IMX6Q) {
		if (data->alarm_temp == data->temp_passive &&
			*temp >= data->temp_passive)
			imx_set_alarm_temp(data, data->temp_critical);
		if (data->alarm_temp == data->temp_critical &&
			*temp < data->temp_passive) {
			imx_set_alarm_temp(data, data->temp_passive);
			dev_dbg(&tz->device, "thermal alarm off: T < %d\n",
				data->alarm_temp / 1000);
		}
	}

	if (*temp != data->last_temp) {
		dev_dbg(&tz->device, "millicelsius: %d\n", *temp);
		data->last_temp = *temp;
	}


	if (!data->irq_enabled && *temp < data->alarm_temp) {
		data->irq_enabled = true;
		enable_irq(data->irq);
	}

	return 0;
}
