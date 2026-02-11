notify_checklist (void)
{
	struct server *serv;
	GSList *list = serv_list;

	while (list)
	{
		serv = list->data;
		if (serv->connected && serv->end_of_motd && !serv->supports_watch && !serv->supports_monitor)
		{
			notify_checklist_for_server (serv);
		}
		list = list->next;
	}
	return 1;
}
