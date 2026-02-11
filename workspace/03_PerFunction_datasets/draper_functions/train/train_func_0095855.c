config_entry_to_option(GtkWidget *entry, gchar **option, gchar *(*func)(const gchar *))
{
	const gchar *buf;

	g_free(*option);
	*option = NULL;
	buf = gtk_entry_get_text(GTK_ENTRY(entry));
	if (buf && strlen(buf) > 0)
		{
		if (func)
			*option = func(buf);
		else
			*option = g_strdup(buf);
		}
}
