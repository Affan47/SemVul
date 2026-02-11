gfire_server_detection_remove_invalid_servers(gfire_server_detector *p_detection, const GList *p_local_ips)
{

	GList *cur = p_detection->tcp_servers;
	while(cur)
	{
		gboolean deleted = FALSE;
		gfire_server *server = (gfire_server*)cur->data;


		const GList *lip = p_local_ips;
		while(lip)
		{
			if(server->ip == *((guint32*)lip->data))
			{
				deleted = TRUE;
				GList *to_delete = cur;
				cur = g_list_next(cur);

				g_free(server);
				p_detection->tcp_servers = g_list_delete_link(p_detection->tcp_servers, to_delete);

				break;
			}
			lip = g_list_next(lip);
		}
		if(deleted)
			continue;


		GList *port = p_detection->excluded_ports;
		while(port)
		{
			if(server->port == *((guint16*)port->data))
			{
				deleted = TRUE;
				GList *to_delete = cur;
				cur = g_list_next(cur);

				g_free(server);
				p_detection->tcp_servers = g_list_delete_link(p_detection->tcp_servers, to_delete);

				break;
			}
			port = g_list_next(port);
		}
		if(deleted)
			continue;

		cur = g_list_next(cur);
	}


	cur = p_detection->udp_servers;
	while(cur)
	{
		gboolean deleted = FALSE;
		gfire_server *server = (gfire_server*)cur->data;


		const GList *lip = p_local_ips;
		while(lip)
		{
			if(server->ip == *((guint32*)lip->data))
			{
				deleted = TRUE;
				GList *to_delete = cur;
				cur = g_list_next(cur);

				g_free(server);
				p_detection->udp_servers = g_list_delete_link(p_detection->udp_servers, to_delete);

				break;
			}
			lip = g_list_next(lip);
		}
		if(deleted)
			continue;


		GList *port = p_detection->excluded_ports;
		while(port)
		{
			if(server->port == *((guint16*)port->data))
			{
				deleted = TRUE;
				GList *to_delete = cur;
				cur = g_list_next(cur);

				g_free(server);
				p_detection->udp_servers = g_list_delete_link(p_detection->udp_servers, to_delete);

				break;
			}
			port = g_list_next(port);
		}
		if(deleted)
			continue;

		cur = g_list_next(cur);
	}
}
