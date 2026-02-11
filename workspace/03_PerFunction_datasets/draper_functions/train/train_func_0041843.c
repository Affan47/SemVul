cpufreq_remove_dev(struct device *dev, struct subsys_interface *sif)
{
	unsigned int cpu = dev->id;
	struct cpufreq_policy *policy = per_cpu(cpufreq_cpu_data, cpu);

	if (!policy)
		return;

	if (cpu_online(cpu)) {
		cpufreq_offline_prepare(cpu);
		cpufreq_offline_finish(cpu);
	}

	cpumask_clear_cpu(cpu, policy->real_cpus);
	remove_cpu_dev_symlink(policy, cpu);

	if (cpumask_empty(policy->real_cpus))
		cpufreq_policy_free(policy, true);
}
