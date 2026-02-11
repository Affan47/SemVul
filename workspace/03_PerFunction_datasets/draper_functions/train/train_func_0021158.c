start_dir_func (GFile      *directory,
		GFileInfo  *info,
		GError    **error,
		gpointer    user_data)
{
	GthSearchTask *task = user_data;
	char          *uri;
	char          *text;

	if (! file_is_visible (task, info))
		return DIR_OP_SKIP;

	uri = g_file_get_parse_name (directory);
	text = g_strdup_printf ("Searching in %s", uri);
	gth_embedded_dialog_set_primary_text (GTH_EMBEDDED_DIALOG (task->priv->dialog), text);

	g_free (text);
	g_free (uri);

	return DIR_OP_CONTINUE;
}
