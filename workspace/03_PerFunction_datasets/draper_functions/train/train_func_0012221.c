set_root_from_doc (GeditFileBrowserPlugin *plugin,
                   GeditDocument          *doc)
{
	GeditFileBrowserPluginPrivate *priv = plugin->priv;
	GFile *file;
	GFile *parent;

	if (doc == NULL)
		return;

	file = gedit_document_get_location (doc);
	if (file == NULL)
		return;

	parent = g_file_get_parent (file);

	if (parent != NULL)
	{
		gedit_file_browser_widget_set_root (priv->tree_widget,
				                    parent,
				                    TRUE);

		g_object_unref (parent);
	}

	g_object_unref (file);
}
