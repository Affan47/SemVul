on_docman_auto_save (gpointer data)
{
	gboolean retval;
	DocmanPlugin *plugin;
	AnjutaDocman *docman;
	AnjutaStatus* status;
	IAnjutaDocument *doc;
	GList *buffers, *node;

	plugin = ANJUTA_PLUGIN_DOCMAN (data);
	docman = ANJUTA_DOCMAN (plugin->docman);
	if (!docman)
		return FALSE;

	if (g_settings_get_boolean (plugin->settings, SAVE_AUTOMATIC) == FALSE)
	{
		plugin->autosave_on = FALSE;
		return FALSE;
	}

	status = anjuta_shell_get_status (docman->shell, NULL);

	retval = TRUE;
	buffers = anjuta_docman_get_all_doc_widgets (docman);
	if (buffers)
	{
		for (node = buffers; node != NULL; node = g_list_next (node))
		{
			doc = IANJUTA_DOCUMENT (node->data);
			if (ianjuta_file_savable_is_dirty (IANJUTA_FILE_SAVABLE (doc), NULL) &&
				!ianjuta_file_savable_is_conflict (IANJUTA_FILE_SAVABLE (doc), NULL))
			{
				GFile* file = ianjuta_file_get_file (IANJUTA_FILE (doc), NULL);
				if (file)
				{
					GError *err = NULL;
					g_object_unref (file);

					ianjuta_file_savable_save (IANJUTA_FILE_SAVABLE (doc), &err);
					if (err)
					{
						gchar *fullmsg;
						const gchar *filename = ianjuta_document_get_filename (doc, NULL);
						fullmsg = g_strdup_printf (_("Autosave failed for %s"), filename);
						anjuta_status (status, fullmsg, 3);
						g_free (fullmsg);
						g_error_free (err);
						retval = FALSE;
					}
				}
			}
		}
		g_list_free (buffers);
	}

	if (retval)
	{
		anjuta_status (status, _("Autosave completed"), 3);
	}
	return retval;
}
