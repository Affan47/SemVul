cpufreq_p4_target(struct cpufreq_policy *policy, unsigned int index)
{
	int i;


	for_each_cpu(i, policy->cpus)
		cpufreq_p4_setdc(i, p4clockmod_table[index].driver_data);

	return 0;
}
