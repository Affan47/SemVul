bmg160_set_power_state(struct bmg160_data *data, bool on)
{
#ifdef CONFIG_PM
	int ret;

	if (on)
		ret = pm_runtime_get_sync(data->dev);
	else {
		pm_runtime_mark_last_busy(data->dev);
		ret = pm_runtime_put_autosuspend(data->dev);
	}

	if (ret < 0) {
		dev_err(data->dev,
			"Failed: bmg160_set_power_state for %d\n", on);
		if (on)
			pm_runtime_put_noidle(data->dev);

		return ret;
	}
#endif

	return 0;
}
