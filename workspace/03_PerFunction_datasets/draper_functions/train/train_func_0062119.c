cpufreq_set_cur_state(struct thermal_cooling_device *cdev,
				 unsigned long state)
{
	struct cpufreq_cooling_device *cpufreq_device = cdev->devdata;
	unsigned int cpu = cpumask_any(&cpufreq_device->allowed_cpus);
	unsigned int clip_freq;


	if (WARN_ON(state > cpufreq_device->max_level))
		return -EINVAL;


	if (cpufreq_device->cpufreq_state == state)
		return 0;

	clip_freq = cpufreq_device->freq_table[state];
	cpufreq_device->cpufreq_state = state;
	cpufreq_device->clipped_freq = clip_freq;

	cpufreq_update_policy(cpu);

	return 0;
}
