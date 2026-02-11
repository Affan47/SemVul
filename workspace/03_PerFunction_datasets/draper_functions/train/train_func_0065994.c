gyrus_session_append_session (GyrusSession *new)
{
	gchar *host, *port, *user, *sep_char, *usetls;
	gchar *name;
	gchar *key;
	GSList *sessions, *element;

	g_return_if_fail (new != NULL);

	if (new->name == NULL)
	{
		gyrus_common_show_message (GTK_WINDOW (window),
					   GTK_MESSAGE_ERROR,
					   _("A session name is required."));
		return;
	}

	key = g_strconcat (PATH_KEY, "StoredSessions", NULL);
	sessions = gconf_client_get_list (conf_client, key,
						  GCONF_VALUE_STRING, NULL);

	element = g_slist_find_custom (sessions, new->name,
						(GCompareFunc) g_ascii_strcasecmp);
	if (element) {
		gchar * msg = g_strdup_printf (_("Session named \"%s\" already exists."),
					       new->name);
		gyrus_common_show_message(GTK_WINDOW (window),
					  GTK_MESSAGE_ERROR, msg);
		g_free (msg);
		g_free (key);
		return;
	}

	name = g_strdup (new->name);
	sessions = g_slist_append (sessions, (gpointer) name);

	gconf_client_set_list (conf_client, key,
			       GCONF_VALUE_STRING, sessions,
			       NULL);
	g_free (key);
	gyrus_session_list_free (sessions);

	host = g_strconcat (PATH_SESSIONS, new->name, "/", "Host", NULL);
	port = g_strconcat (PATH_SESSIONS, new->name, "/", "Port", NULL);
	user = g_strconcat (PATH_SESSIONS, new->name, "/", "User", NULL);
	sep_char = g_strconcat (PATH_SESSIONS, new->name, "/", "SeparatorChar", NULL);
	usetls = g_strconcat (PATH_SESSIONS, new->name, "/", "UseTLS", NULL);

	gconf_client_set_string (conf_client, host, new->host, NULL);
	gconf_client_set_int    (conf_client, port, new->port, NULL);
	gconf_client_set_string (conf_client, user, new->user, NULL);
	gconf_client_set_string (conf_client, sep_char, new->sep_char, NULL);
	gconf_client_set_bool   (conf_client, usetls, new->usetls, NULL);

	g_free (host);
	g_free (port);
	g_free (user);
	g_free (sep_char);
	g_free (usetls);

	gyrus_session_load_gconf_settings();
}
