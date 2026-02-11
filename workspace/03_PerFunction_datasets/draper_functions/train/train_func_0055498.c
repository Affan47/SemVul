_e2_command_line_insert_action
	(gpointer from, E2_ActionRuntime *art)
{
	gchar *arg = (gchar *)art->data;

	g_strstrip (arg);
	gchar *str_down = g_utf8_strdown (arg, -1);
	gboolean escape = g_str_equal (arg, _A(107));
	gboolean quote = (escape) ? FALSE : g_str_equal (arg, _A(112));
	g_free (str_down);

#ifdef E2_REFRESH_DEBUG
	printd (DEBUG, "disable refresh, insert action");
#endif
	e2_filelist_disable_refresh ();

	gchar *utf;
	GString *cmd = g_string_sized_new (128);

	GList *tmp, *base;
	base = tmp = e2_fileview_get_selected_local (curr_view);
	for (; tmp != NULL; tmp=tmp->next)
	{
		utf = F_FILENAME_FROM_LOCALE (((FileInfo *) tmp->data)->filename);
		if (escape)
		{
			gchar *temp = e2_utf8_escape (utf, ' ');
			F_FREE (utf);
			utf = temp;
		}
		cmd = g_string_append_c (cmd, ' ');
		if (quote)
			g_string_append_printf (cmd, "\"%s\"", utf);
		else
			cmd = g_string_append (cmd, utf);
		if (escape)
			g_free (utf);
		else
			F_FREE (utf);
	}

	GtkWidget *entry = (from == NULL) ? NULL : GTK_WIDGET (from);
	E2_CommandLineRuntime *rt = NULL;
	_e2_command_line_get (&entry, &rt);
	gint cursor = gtk_editable_get_position (GTK_EDITABLE (entry));
	gtk_editable_insert_text (GTK_EDITABLE (entry), cmd->str,
		cmd->len, &cursor);
	gtk_editable_set_position (GTK_EDITABLE (entry), cursor);

	g_string_free (cmd, TRUE);
	g_list_free (base);

#ifdef E2_REFRESH_DEBUG
	printd (DEBUG, "enable refresh, insert action");
#endif
	e2_filelist_enable_refresh();
	return TRUE;
}
