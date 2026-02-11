file_enumerate_next_cb (GObject      *object,
                        GAsyncResult *result,
                        gpointer      user_data)
{
	TrackerCrawler *crawler;
	EnumeratorData *ed;
	GFileEnumerator *enumerator;
	GFile *parent, *child;
	GFileInfo *info;
	GList *files, *l;
	GError *error = NULL;
	gboolean cancelled;

	enumerator = G_FILE_ENUMERATOR (object);

	ed = user_data;
	crawler = ed->crawler;
	cancelled = g_cancellable_is_cancelled (ed->cancellable);
	parent = g_file_enumerator_get_container (enumerator);

	files = g_file_enumerator_next_files_finish (enumerator,
	                                             result,
	                                             &error);

	if (error || !files || !crawler->priv->is_running) {
		if (error && !cancelled) {
			g_critical ("Could not crawl through directory: %s", error->message);
			g_error_free (error);
		}


		if (files) {
			g_list_foreach (files, (GFunc) g_object_unref, NULL);
			g_list_free (files);
		}

		if (!cancelled) {
			enumerator_data_process (parent, ed);
		}

		g_file_enumerator_close_async (enumerator,
		                               G_PRIORITY_DEFAULT,
		                               NULL,
		                               file_enumerator_close_cb,
		                               g_object_ref (crawler));
		enumerator_data_free (ed);
		g_object_unref (enumerator);

		return;
	}

	for (l = files; l; l = l->next) {
		const gchar *child_name;
		gboolean is_dir;

		info = l->data;

		child_name = g_file_info_get_name (info);
		child = g_file_get_child (parent, child_name);
		is_dir = g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY;

		if (crawler->priv->file_attributes) {

			g_object_set_qdata_full (G_OBJECT (child),
						 file_info_quark,
						 g_object_ref (info),
						 (GDestroyNotify) g_object_unref);
		}

		directory_processing_data_add_child (ed->dir_info, child, is_dir);

		g_object_unref (child);
		g_object_unref (info);
	}

	g_list_free (files);


	file_enumerate_next (enumerator, ed);
}
