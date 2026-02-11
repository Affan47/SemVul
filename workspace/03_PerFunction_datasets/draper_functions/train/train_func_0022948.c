gkrellm_net_mon_next(void)
	{
	gchar	*name = NULL;

	if (net_mon_sys_list)
		{
		name = ((NetMon *) (net_mon_sys_list->data))->name;
		net_mon_sys_list = net_mon_sys_list->next;
		}
	return name;
	}
