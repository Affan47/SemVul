cpufreq_cooling_unregister(struct thermal_cooling_device *cdev)
{
	struct cpufreq_cooling_device *cpufreq_dev;

	if (!cdev)
		return;

	cpufreq_dev = cdev->devdata;


	mutex_lock(&cooling_cpufreq_lock);
	if (!--cpufreq_dev_count)
		cpufreq_unregister_notifier(&thermal_cpufreq_notifier_block,
					    CPUFREQ_POLICY_NOTIFIER);

	mutex_lock(&cooling_list_lock);
	list_del(&cpufreq_dev->node);
	mutex_unlock(&cooling_list_lock);

	mutex_unlock(&cooling_cpufreq_lock);

	thermal_cooling_device_unregister(cpufreq_dev->cool_dev);
	release_idr(&cpufreq_idr, cpufreq_dev->id);
	kfree(cpufreq_dev->dyn_power_table);
	kfree(cpufreq_dev->time_in_idle_timestamp);
	kfree(cpufreq_dev->time_in_idle);
	kfree(cpufreq_dev->freq_table);
	kfree(cpufreq_dev);
}
