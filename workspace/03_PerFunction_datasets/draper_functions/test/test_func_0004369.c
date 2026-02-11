save_file_async (NemoBookmarkList *bookmarks,
		 GAsyncReadyCallback callback)
{
	GFile *file;
	GList *l;
	GString *bookmark_string;
    GFile *parent;
    char *path;


	if (bookmarks->monitor != NULL) {
		g_file_monitor_cancel (bookmarks->monitor);
		bookmarks->monitor = NULL;
	}

	file = nemo_bookmark_list_get_file ();
	bookmark_string = g_string_new (NULL);

	for (l = bookmarks->list; l; l = l->next) {
		NemoBookmark *bookmark;

		bookmark = NEMO_BOOKMARK (l->data);


		if (nemo_bookmark_get_has_custom_name (bookmark)) {
			const char *label;
			char *uri;
			label = nemo_bookmark_get_name (bookmark);
			uri = nemo_bookmark_get_uri (bookmark);
			g_string_append_printf (bookmark_string,
						"%s %s\n", uri, label);
			g_free (uri);
		} else {
			char *uri;
			uri = nemo_bookmark_get_uri (bookmark);
			g_string_append_printf (bookmark_string, "%s\n", uri);
			g_free (uri);
		}
	}


	g_object_ref (bookmarks);

    parent = g_file_get_parent (file);
    path = g_file_get_path (parent);
    g_mkdir_with_parents (path, 0700);
    g_free (path);
    g_object_unref (parent);

	g_file_replace_contents_async (file, bookmark_string->str,
				       bookmark_string->len, NULL,
				       FALSE, 0, NULL, callback,
				       bookmarks);

	g_object_unref (file);
}
