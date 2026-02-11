prefill_possible_map(void)
{
	int i, possible;


	if (!num_processors)
		num_processors = 1;

	i = setup_max_cpus ?: 1;
	if (setup_possible_cpus == -1) {
		possible = num_processors;
#ifdef CONFIG_HOTPLUG_CPU
		if (setup_max_cpus)
			possible += disabled_cpus;
#else
		if (possible > i)
			possible = i;
#endif
	} else
		possible = setup_possible_cpus;

	total_cpus = max_t(int, possible, num_processors + disabled_cpus);


	if (possible > nr_cpu_ids) {
		pr_warn("%d Processors exceeds NR_CPUS limit of %d\n",
			possible, nr_cpu_ids);
		possible = nr_cpu_ids;
	}

#ifdef CONFIG_HOTPLUG_CPU
	if (!setup_max_cpus)
#endif
	if (possible > i) {
		pr_warn("%d Processors exceeds max_cpus limit of %u\n",
			possible, setup_max_cpus);
		possible = i;
	}

	pr_info("Allowing %d CPUs, %d hotplug CPUs\n",
		possible, max_t(int, possible - num_processors, 0));

	for (i = 0; i < possible; i++)
		set_cpu_possible(i, true);
	for (; i < NR_CPUS; i++)
		set_cpu_possible(i, false);

	nr_cpu_ids = possible;
}
