max6697_update_device(struct device *dev)
{
	struct max6697_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct max6697_data *ret = data;
	int val;
	int i;
	u32 alarms;

	mutex_lock(&data->update_lock);

	if (data->valid &&
	    !time_after(jiffies, data->last_updated
			+ msecs_to_jiffies(data->update_interval)))
		goto abort;

	for (i = 0; i < data->chip->channels; i++) {
		if (data->chip->have_ext & (1 << i)) {
			val = i2c_smbus_read_byte_data(client,
						       MAX6697_REG_TEMP_EXT[i]);
			if (unlikely(val < 0)) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->temp[i][MAX6697_TEMP_EXT] = val;
		}

		val = i2c_smbus_read_byte_data(client, MAX6697_REG_TEMP[i]);
		if (unlikely(val < 0)) {
			ret = ERR_PTR(val);
			goto abort;
		}
		data->temp[i][MAX6697_TEMP_INPUT] = val;

		val = i2c_smbus_read_byte_data(client, MAX6697_REG_MAX[i]);
		if (unlikely(val < 0)) {
			ret = ERR_PTR(val);
			goto abort;
		}
		data->temp[i][MAX6697_TEMP_MAX] = val;

		if (data->chip->have_crit & (1 << i)) {
			val = i2c_smbus_read_byte_data(client,
						       MAX6697_REG_CRIT[i]);
			if (unlikely(val < 0)) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->temp[i][MAX6697_TEMP_CRIT] = val;
		}
	}

	alarms = 0;
	for (i = 0; i < 3; i++) {
		val = i2c_smbus_read_byte_data(client, MAX6697_REG_STAT(i));
		if (unlikely(val < 0)) {
			ret = ERR_PTR(val);
			goto abort;
		}
		alarms = (alarms << 8) | val;
	}
	data->alarms = alarms;
	data->last_updated = jiffies;
	data->valid = true;
abort:
	mutex_unlock(&data->update_lock);

	return ret;
}
