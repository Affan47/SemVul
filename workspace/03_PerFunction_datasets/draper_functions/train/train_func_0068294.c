gfire_set_game_status(gfire_data *p_gfire, const gfire_game_data *p_data)
{
	if(!p_gfire || !p_data)
		return;

	gboolean notify = purple_account_get_bool(purple_connection_get_account(p_gfire->gc),
											  "ingamenotificationnorm", FALSE);
	if (notify)
	{
		gchar *game_name = gfire_game_name(p_data->id, TRUE);
		purple_notify_message(NULL, PURPLE_NOTIFY_MSG_INFO, _("Ingame status"),
							  NN(game_name), _("Your status has been changed."), NULL, NULL);
		g_free(game_name);
	}

#ifdef HAVE_GTK
	if(p_data->id && p_data->ip.value)
		gfire_server_browser_add_recent(p_gfire->server_browser, p_data->id, p_data->ip.value, p_data->port);
#endif

	guint16 len = gfire_proto_create_join_game(p_data);
	if(len > 0) gfire_send(p_gfire->gc, len);
}
