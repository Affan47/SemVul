maki_dbus_who (const gchar* server, const gchar* mask, gboolean operators_only, GError** error)
{
	makiServer* serv;
	makiInstance* inst = maki_instance_get_default();

	if ((serv = maki_instance_get_server(inst, server)) != NULL)
	{
		if (operators_only)
		{
			maki_server_send_printf(serv, "WHO %s o", mask);
		}
		else
		{
			maki_server_send_printf(serv, "WHO %s", mask);
		}
	}

	return TRUE;
}
