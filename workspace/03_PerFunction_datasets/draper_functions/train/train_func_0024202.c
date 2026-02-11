apds9960_set_power_state(struct apds9960_data *data, bool on)
{
	struct device *dev = &data->client->dev;
	int ret = 0;

	mutex_lock(&data->lock);

	if (on) {
		int suspended;

		suspended = pm_runtime_suspended(dev);
		ret = pm_runtime_get_sync(dev);


		if (suspended)
			usleep_range(data->als_adc_int_us,
				     APDS9960_MAX_INT_TIME_IN_US);
	} else {
		pm_runtime_mark_last_busy(dev);
		ret = pm_runtime_put_autosuspend(dev);
	}

	mutex_unlock(&data->lock);

	return ret;
}
