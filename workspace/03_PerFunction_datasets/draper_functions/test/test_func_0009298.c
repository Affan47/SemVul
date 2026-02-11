gyrus_session_get_with_name (const gchar *name)
{
	GError *error = NULL;
	GyrusSession *aux = NULL;
	gchar *host;
	gchar *port;
	gchar *user;
	gchar *sep_char;
	gchar *usetls;

	aux = g_new0 (GyrusSession, 1);
	host = g_strconcat (PATH_SESSIONS, name, "/", "Host", NULL);
	port = g_strconcat (PATH_SESSIONS, name, "/", "Port", NULL);
	user = g_strconcat (PATH_SESSIONS, name, "/", "User", NULL);
	sep_char = g_strconcat (PATH_SESSIONS, name, "/", "SeparatorChar", NULL);
	usetls = g_strconcat (PATH_SESSIONS, name, "/", "UseTLS", NULL);

	aux->name = g_strdup (name);
	aux->host = gconf_client_get_string (conf_client, host, NULL);
	aux->port = gconf_client_get_int (conf_client, port, NULL);
	aux->user = gconf_client_get_string (conf_client, user, NULL);
	aux->sep_char = gconf_client_get_string (conf_client, sep_char,
						 &error);
	if (aux->sep_char == NULL)
		aux->sep_char = g_strdup (".");
	else if (error) {
		aux->sep_char = g_strdup (".");
		g_warning ("%s", error->message);
		g_error_free (error);
	}

	aux->usetls = gconf_client_get_bool (conf_client, usetls, NULL);

	g_free (host);
	g_free (port);
	g_free (user);
	g_free (sep_char);
	g_free (usetls);

	return aux;
}
