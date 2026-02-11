dup_cpu_alert(void)
	{
	GList	*list;
	CpuMon	*cpu;

	for (list = cpu_mon_list; list; list = list->next)
		{
		cpu = (CpuMon *) list->data;
		gkrellm_alert_dup(&cpu->alert, cpu_alert);
		gkrellm_alert_trigger_connect(cpu->alert, cb_alert_trigger, cpu);
		gkrellm_alert_command_process_connect(cpu->alert,
					cb_command_process, cpu);
		}
	}
