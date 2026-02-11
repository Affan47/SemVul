maki_dbus_mode (const gchar* server, const gchar* target, const gchar* mode, GError** error)
{
	makiServer* serv;
	makiInstance* inst = maki_instance_get_default();

	if ((serv = maki_instance_get_server(inst, server)) != NULL)
	{
		if (mode[0])
		{
			maki_server_send_printf(serv, "MODE %s %s", target, mode);
		}
		else
		{
			maki_server_send_printf(serv, "MODE %s", target);
		}
	}

	return TRUE;
}
