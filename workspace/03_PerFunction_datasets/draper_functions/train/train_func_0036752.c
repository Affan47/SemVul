on_close_all_file_activate (GtkAction *action, gpointer user_data)
{
	GList *buffers;
	AnjutaDocman *docman;
	DocmanPlugin *plugin;
	plugin = ANJUTA_PLUGIN_DOCMAN (user_data);
	docman = ANJUTA_DOCMAN (plugin->docman);


	buffers = anjuta_docman_get_all_doc_widgets (docman);
	if (buffers)
	{
		GList *node;
		node = buffers;
		while (node)
		{
			IAnjutaDocument *doc;
			GList* next;
			doc = IANJUTA_DOCUMENT (node->data);
			next = g_list_next (node);
			if (doc)
			{
				if (!ianjuta_file_savable_is_dirty (IANJUTA_FILE_SAVABLE (doc), NULL))
				{
					anjuta_docman_remove_document (docman, doc);
				}
			}
			node = next;
		}
		g_list_free (buffers);
	}
}
