debugger_print_finish (Debugger *debugger, const GDBMIValue *mi_results, const GList *cli_results, GError *error)
{
	gchar *ptr = NULL;
	gchar *tmp;
	GList *list, *node;
	IAnjutaDebuggerCallback callback = debugger->priv->current_cmd.callback;
	gpointer user_data = debugger->priv->current_cmd.user_data;


	list = gdb_util_remove_blank_lines (cli_results);
	if (g_list_length (list) < 1)
	{
		tmp = NULL;
	}
	else
	{
		tmp = strchr ((gchar *) list->data, '=');
	}
	if (tmp != NULL)
	{
		ptr = g_strdup (tmp);
		for (node = list ? list->next : NULL; node != NULL; node = node->next)
		{
			tmp = ptr;
			ptr = g_strconcat (tmp, (gchar *) node->data, NULL);
			g_free (tmp);
		}
	}

	callback (ptr, user_data, NULL);
	g_free (ptr);
}
