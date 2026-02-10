abituguru3_update_device(struct device *dev)
{
	int i;
	struct abituguru3_data *data = dev_get_drvdata(dev);

	mutex_lock(&data->update_lock);
	if (!data->valid || time_after(jiffies, data->last_updated + HZ)) {

		data->valid = 0;

		if (abituguru3_read_increment_offset(data,
				ABIT_UGURU3_SETTINGS_BANK,
				ABIT_UGURU3_ALARMS_START,
				1, data->alarms, 48/8) != (48/8))
			goto LEAVE_UPDATE;

		for (i = 0; i < 32; i++) {
			if (abituguru3_read(data, ABIT_UGURU3_SENSORS_BANK,
					ABIT_UGURU3_VALUES_START + i,
					1, &data->value[i]) != 1)
				goto LEAVE_UPDATE;
			if (abituguru3_read_increment_offset(data,
					ABIT_UGURU3_SETTINGS_BANK,
					ABIT_UGURU3_SETTINGS_START + i * 3,
					1,
					data->settings[i], 3) != 3)
				goto LEAVE_UPDATE;
		}

		for (i = 0; i < 16; i++) {
			if (abituguru3_read(data, ABIT_UGURU3_SENSORS_BANK,
					ABIT_UGURU3_VALUES_START + 32 + i,
					1, &data->value[32 + i]) != 1)
				goto LEAVE_UPDATE;
			if (abituguru3_read_increment_offset(data,
					ABIT_UGURU3_SETTINGS_BANK,
					ABIT_UGURU3_SETTINGS_START + 32 * 3 +
						i * 2, 1,
					data->settings[32 + i], 2) != 2)
				goto LEAVE_UPDATE;
		}
		data->last_updated = jiffies;
		data->valid = 1;
	}
LEAVE_UPDATE:
	mutex_unlock(&data->update_lock);
	if (data->valid)
		return data;
	else
		return NULL;
}
