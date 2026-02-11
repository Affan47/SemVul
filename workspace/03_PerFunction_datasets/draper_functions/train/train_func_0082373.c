get_measure_start_info(unsigned int cpu,
				  struct avg_perf_cpu_info *cpu_info)
{
	unsigned long min, max;
	uint64_t aperf, mperf;
	int ret;

	cpu_info->is_valid = 0;

	if (cpufreq_get_hardware_limits(cpu, &min, &max))
		return -EINVAL;

	cpu_info->max_freq = max;

	ret = get_aperf_mperf(cpu, &aperf, &mperf);
	if (ret < 0)
		return -EINVAL;

	cpu_info->saved_aperf = aperf;
	cpu_info->saved_mperf = mperf;
	cpu_info->is_valid = 1;

	return 0;
}
