exporter_export_to_xml (GSQLContent *content, gchar *file, gchar *encoding, gboolean headers)
{
	GSQL_TRACE_FUNC;

	GIOChannel *ioc = NULL;
	GIOStatus status;
	gchar msg[GSQL_MESSAGE_LEN];
	GError *err = NULL;
	gboolean finished = FALSE;
	GtkTreeView *tv;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *buffer;
	gint ncolumns;
	GList *columns = NULL;
	GtkTreeViewColumn *column;
	GtkWidget *column_header;
	gchar *name;
	GSQLWorkspace *workspace;


	g_return_if_fail (content != NULL);
	name = gsql_content_get_name (content);
	workspace = gsql_session_get_workspace (content->session);


	GSQL_DEBUG ("Open [%s] for writing", file);
	ioc = g_io_channel_new_file (name, "w+", &err);

	GSQL_DEBUG ("11");

	if (ioc == NULL)
	{
		memset (msg, 0, GSQL_MESSAGE_LEN);
		g_snprintf (msg, GSQL_MESSAGE_LEN, N_("Export failed:['%s'] %s"),
					name, err->message);
		gsql_message_add (workspace, GSQL_MESSAGE_ERROR, msg);
		return;
	};
	GSQL_DEBUG ("22");
	if (encoding)
		g_io_channel_set_encoding (ioc, encoding, &err);


	if (columns)
		g_list_free (columns);

	g_io_channel_flush (ioc, &err);
	g_io_channel_unref (ioc);

	gsql_message_add (workspace, GSQL_MESSAGE_WARNING,
					  "The XML routines is not implemented yet. Please select other type.");

	return;
}
