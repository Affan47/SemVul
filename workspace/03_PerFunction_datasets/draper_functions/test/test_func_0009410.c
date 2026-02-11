gdb_util_remove_blank_lines (const GList * lines)
{
	GList *list, *node;
	gchar *str;

	if (lines)
		list = g_list_copy ((GList*)lines);
	else
		list = NULL;

	node = list;
	while (node)
	{
		str = node->data;
		node = g_list_next (node);
		if (!str)
		{
			list = g_list_remove (list, str);
			continue;
		}
		if (strlen (g_strchomp (str)) < 1)
			list = g_list_remove (list, str);
	}
	return list;
}
