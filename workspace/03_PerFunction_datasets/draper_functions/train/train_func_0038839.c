vclog_dir_activated(G_GNUC_UNUSED GtkMenuItem * menuitem, G_GNUC_UNUSED gpointer gdata)
{
	gchar *base_name = NULL;
	gchar *text = NULL;
	const VC_RECORD *vc;
	GeanyDocument *doc;

	doc = document_get_current();
	g_return_if_fail(doc != NULL && doc->file_name != NULL);

	base_name = g_path_get_dirname(doc->file_name);

	vc = find_vc(base_name);
	g_return_if_fail(vc);

	execute_command(vc, &text, NULL, base_name, VC_COMMAND_LOG_DIR, NULL, NULL);
	if (text)
	{
		show_output(text, "*VC-LOG*", NULL, NULL, 0);
		g_free(text);
	}

	g_free(base_name);
}
