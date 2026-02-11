cpufreq_get_hardware_limits(unsigned int cpu,
				unsigned long *min,
				unsigned long *max)
{
	int ret;
	if ((!min) || (!max))
		return -EINVAL;
	ret = sysfs_get_hardware_limits(cpu, min, max);
	if (ret)
		ret = proc_get_hardware_limits(cpu, min, max);
	return (ret);
}
