maki_in_err_nosuch (makiServer* serv, gchar* remaining, gint numeric)
{
	const gchar* reason = "";
	const gchar* type = "";
	gchar** arguments;
	gchar** tmp;

	if (!remaining)
	{
		return;
	}

	tmp = g_strsplit(remaining, " ", 2);

	if (g_strv_length(tmp) < 1)
	{
		g_strfreev(tmp);
		return;
	}

	switch (numeric)
	{

		case 401:
			reason = "nick";
			type = "n";
			break;

		case 402:
			reason = "server";
			type = "s";
			break;

		case 403:
			reason = "channel";
			type = "c";
			break;
		default:
			g_warn_if_reached();
			break;
	}

	arguments = i_strv_new(NULL, tmp[0], NULL);

	maki_dbus_emit_error(maki_server_name(serv), "no_such", reason, arguments);
	maki_dbus_emit_no_such(maki_server_name(serv), tmp[0], type);

	g_free(arguments);

	g_strfreev(tmp);
}
