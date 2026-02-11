list_local (DebuggerJs* object, struct Task *task)
{
	DebuggerJsPrivate *priv = DEBUGGER_JS_PRIVATE(object);
	GList *var = NULL;
	gint i, size;
	gchar *k;
	gchar *line = debugger_server_get_line (priv->server);

	for (k = line, i = 0, size = strlen (line); i <= size; i++)
	{
		if (line [i] == ',')
		{
			line [i] = '\0';
			var = g_list_append (var, g_strdup (k));
			k = line + i + 1;
		}
	}
	g_free (line);

	return var;
}
