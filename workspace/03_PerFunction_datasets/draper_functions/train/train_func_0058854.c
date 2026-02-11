client_sys_cpu_init(void)
	{
	GList	*list;
	Cpu		*cpu;
	gint	n;


	for (n = 0; n < n_cpus; ++ n)
		{
		cpu = g_new0(Cpu, 1);
		if (instance_list && (list = g_list_nth(instance_list, n)) != NULL)
			{
			cpu->instance = GPOINTER_TO_INT(list->data);
			gkrellm_cpu_add_instance(cpu->instance);
			}
		else
			cpu->instance = n;
		cpu_list = g_list_append(cpu_list, cpu);
		}
	gkrellm_cpu_set_number_of_cpus(n_cpus);
	if (!nice_time_supported)
		gkrellm_cpu_nice_time_unsupported();


	gkrellm_cpu_client_divert(cpu_read_data);
	}
