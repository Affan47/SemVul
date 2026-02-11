cpufreq_set_cur_state(unsigned int cpu, int state)
{
	int i;

	if (!cpu_has_cpufreq(cpu))
		return 0;

	reduction_pctg(cpu) = state;


	for_each_online_cpu(i) {
		if (topology_physical_package_id(i) ==
		    topology_physical_package_id(cpu))
			cpufreq_update_policy(i);
	}
	return 0;
}
