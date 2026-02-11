maki_out_join (makiServer* serv, const gchar* channel, const gchar* key)
{
	g_return_if_fail(serv != NULL);
	g_return_if_fail(channel != NULL);

	if (key != NULL && key[0])
	{
		maki_server_send_printf(serv, "JOIN %s %s", channel, key);
	}
	else
	{
		maki_server_send_printf(serv, "JOIN %s", channel);
	}
}
