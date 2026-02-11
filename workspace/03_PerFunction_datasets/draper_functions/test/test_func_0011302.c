dpm_resume_noirq(pm_message_t state)
{
	struct device *dev;
	ktime_t starttime = ktime_get();

	trace_suspend_resume(TPS("dpm_resume_noirq"), state.event, true);
	mutex_lock(&dpm_list_mtx);
	pm_transition = state;


	list_for_each_entry(dev, &dpm_noirq_list, power.entry) {
		reinit_completion(&dev->power.completion);
		if (is_async(dev)) {
			get_device(dev);
			async_schedule(async_resume_noirq, dev);
		}
	}

	while (!list_empty(&dpm_noirq_list)) {
		dev = to_device(dpm_noirq_list.next);
		get_device(dev);
		list_move_tail(&dev->power.entry, &dpm_late_early_list);
		mutex_unlock(&dpm_list_mtx);

		if (!is_async(dev)) {
			int error;

			error = device_resume_noirq(dev, state, false);
			if (error) {
				suspend_stats.failed_resume_noirq++;
				dpm_save_failed_step(SUSPEND_RESUME_NOIRQ);
				dpm_save_failed_dev(dev_name(dev));
				pm_dev_err(dev, state, " noirq", error);
			}
		}

		mutex_lock(&dpm_list_mtx);
		put_device(dev);
	}
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	dpm_show_time(starttime, state, "noirq");
	resume_device_irqs();
	device_wakeup_disarm_wake_irqs();
	cpuidle_resume();
	trace_suspend_resume(TPS("dpm_resume_noirq"), state.event, false);
}
