fcoe_select_cpu(void)
{
	static unsigned int selected_cpu;

	selected_cpu = cpumask_next(selected_cpu, cpu_online_mask);
	if (selected_cpu >= nr_cpu_ids)
		selected_cpu = cpumask_first(cpu_online_mask);

	return selected_cpu;
}
