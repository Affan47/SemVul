amd_uncore_cpu_dead(unsigned int cpu)
{
	if (amd_uncore_nb)
		uncore_dead(cpu, amd_uncore_nb);

	if (amd_uncore_l2)
		uncore_dead(cpu, amd_uncore_l2);
}
