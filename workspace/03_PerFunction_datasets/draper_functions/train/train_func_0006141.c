rapl_cpu_exit(int cpu)
{
	struct rapl_pmu *pmu = per_cpu(rapl_pmu, cpu);
	int i, phys_id = topology_physical_package_id(cpu);
	int target = -1;


	for_each_online_cpu(i) {
		if (i == cpu)
			continue;
		if (phys_id == topology_physical_package_id(i)) {
			target = i;
			break;
		}
	}


	if (cpumask_test_and_clear_cpu(cpu, &rapl_cpu_mask) && target >= 0)
		cpumask_set_cpu(target, &rapl_cpu_mask);

	WARN_ON(cpumask_empty(&rapl_cpu_mask));


	if (target >= 0)
		perf_pmu_migrate_context(pmu->pmu, cpu, target);


	rapl_stop_hrtimer(pmu);
}
