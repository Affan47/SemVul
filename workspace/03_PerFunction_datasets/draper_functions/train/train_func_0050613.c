cpufreq_quick_get_max(unsigned int cpu)
{
	struct cpufreq_policy *policy = cpufreq_cpu_get(cpu);
	unsigned int ret_freq = 0;

	if (policy) {
		ret_freq = policy->max;
		cpufreq_cpu_put(policy);
	}

	return ret_freq;
}
