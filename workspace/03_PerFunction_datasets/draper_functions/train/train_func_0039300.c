maki_in_rpl_motd (makiServer* serv, gchar* remaining, gboolean is_end)
{
	if (!remaining)
	{
		return;
	}

	if (is_end)
	{
		maki_dbus_emit_motd(maki_server_name(serv), "");
	}
	else
	{
		maki_dbus_emit_motd(maki_server_name(serv), maki_remove_colon(remaining));
	}
}
