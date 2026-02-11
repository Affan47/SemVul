update_inet(GkrellmdMonitor *mon, gboolean first_update)
	{
	GList		*list;
	InetData	*in;
	static gint	check_tcp;


	if (!first_update && !GK.second_tick)
		return;

	if (first_update || check_tcp == 0)
		{
		gkrellm_free_glist_and_data(&inet_dead_list);
		inet_new = FALSE;
		for (list = inet_list; list; list = list->next)
			{
			in = (InetData *) list->data;
			in->alive = FALSE;
			in->new_connection = FALSE;
			}

		gkrellm_sys_inet_read_tcp_data();

		for (list = inet_list; list; )
			{
			in = (InetData *) list->data;
			if (!in->alive)
				{
				if (list == inet_list)
					inet_list = inet_list->next;
				list = g_list_remove(list, in);
				inet_dead_list = g_list_append(inet_dead_list, in);
				}
			else
				list = list->next;
			}
		if (inet_new || inet_dead_list)
			gkrellmd_need_serve(mon);
		}
	check_tcp = (check_tcp + 1) % _GK.inet_interval;
	}
