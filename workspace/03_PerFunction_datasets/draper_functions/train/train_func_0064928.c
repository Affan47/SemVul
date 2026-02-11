maki_dbus_support_chantypes (const gchar* server, gchar** chantypes, GError** error)
{
	makiServer* serv;
	makiInstance* inst = maki_instance_get_default();

	*chantypes = NULL;

	if ((serv = maki_instance_get_server(inst, server)) != NULL)
	{
		*chantypes = g_strdup(maki_server_support(serv, MAKI_SERVER_SUPPORT_CHANTYPES));
	}

	maki_ensure_string(chantypes);

	return TRUE;
}
