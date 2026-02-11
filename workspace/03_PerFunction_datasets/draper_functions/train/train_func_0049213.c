search_filter_file_command_finalize (GObject *object)
{
	SearchFilterFileCommand* cmd = SEARCH_FILTER_FILE_COMMAND(object);

	if (cmd->priv->file)
		g_object_unref (cmd->priv->file);
	g_free (cmd->priv->mime_types);

	G_OBJECT_CLASS (search_filter_file_command_parent_class)->finalize (object);
}
