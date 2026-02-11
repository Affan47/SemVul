maki_dbus_ctcp (const gchar* server, const gchar* target, const gchar* message, GError** error)
{
	makiServer* serv;
	makiInstance* inst = maki_instance_get_default();

	if ((serv = maki_instance_get_server(inst, server)) != NULL)
	{
		maki_server_send_printf(serv, "PRIVMSG %s :\001%s\001", target, message);

		maki_dbus_emit_ctcp(server, maki_user_from(maki_server_user(serv)), target, message);
		maki_server_log(serv, target, "=%s= %s", maki_user_nick(maki_server_user(serv)), message);
	}

	return TRUE;
}
