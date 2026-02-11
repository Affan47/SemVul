dpm_suspend_late(pm_message_t state)
{
	ktime_t starttime = ktime_get();
	int error = 0;

	trace_suspend_resume(TPS("dpm_suspend_late"), state.event, true);
	mutex_lock(&dpm_list_mtx);
	pm_transition = state;
	async_error = 0;

	while (!list_empty(&dpm_suspended_list)) {
		struct device *dev = to_device(dpm_suspended_list.prev);

		get_device(dev);
		mutex_unlock(&dpm_list_mtx);

		error = device_suspend_late(dev);

		mutex_lock(&dpm_list_mtx);
		if (!list_empty(&dev->power.entry))
			list_move(&dev->power.entry, &dpm_late_early_list);

		if (error) {
			pm_dev_err(dev, state, " late", error);
			dpm_save_failed_dev(dev_name(dev));
			put_device(dev);
			break;
		}
		put_device(dev);

		if (async_error)
			break;
	}
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	if (!error)
		error = async_error;
	if (error) {
		suspend_stats.failed_suspend_late++;
		dpm_save_failed_step(SUSPEND_SUSPEND_LATE);
		dpm_resume_early(resume_event(state));
	} else {
		dpm_show_time(starttime, state, "late");
	}
	trace_suspend_resume(TPS("dpm_suspend_late"), state.event, false);
	return error;
}
