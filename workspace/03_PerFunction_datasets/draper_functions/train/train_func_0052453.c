rapl_cpu_init(int cpu)
{
	int i, phys_id = topology_physical_package_id(cpu);


	for_each_cpu(i, &rapl_cpu_mask) {
		if (phys_id == topology_physical_package_id(i))
			return;
	}

	cpumask_set_cpu(cpu, &rapl_cpu_mask);
}
