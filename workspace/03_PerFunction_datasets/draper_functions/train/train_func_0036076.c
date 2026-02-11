acpi_thermal_cpufreq_notifier(struct notifier_block *nb,
					 unsigned long event, void *data)
{
	struct cpufreq_policy *policy = data;
	unsigned long max_freq = 0;

	if (event != CPUFREQ_ADJUST)
		goto out;

	max_freq = (
	    policy->cpuinfo.max_freq *
	    (100 - reduction_pctg(policy->cpu) * 20)
	) / 100;

	cpufreq_verify_within_limits(policy, 0, max_freq);

      out:
	return 0;
}
