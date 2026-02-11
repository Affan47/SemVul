__target_intermediate(struct cpufreq_policy *policy,
				 struct cpufreq_freqs *freqs, int index)
{
	int ret;

	freqs->new = cpufreq_driver->get_intermediate(policy, index);


	if (!freqs->new)
		return 0;

	pr_debug("%s: cpu: %d, switching to intermediate freq: oldfreq: %u, intermediate freq: %u\n",
		 __func__, policy->cpu, freqs->old, freqs->new);

	cpufreq_freq_transition_begin(policy, freqs);
	ret = cpufreq_driver->target_intermediate(policy, index);
	cpufreq_freq_transition_end(policy, freqs, ret);

	if (ret)
		pr_err("%s: Failed to change to intermediate frequency: %d\n",
		       __func__, ret);

	return ret;
}
