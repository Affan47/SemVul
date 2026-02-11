default_cpu_mask_to_apicid_and(const struct cpumask *cpumask,
				   const struct cpumask *andmask,
				   unsigned int *apicid)
{
	unsigned int cpu;

	for_each_cpu_and(cpu, cpumask, andmask) {
		if (cpumask_test_cpu(cpu, cpu_online_mask))
			break;
	}

	if (likely(cpu < nr_cpu_ids)) {
		*apicid = per_cpu(x86_cpu_to_apicid, cpu);
		return 0;
	}

	return -EINVAL;
}
