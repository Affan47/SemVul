local_store_rename_folder_sync (CamelStore *store,
                                const gchar *old,
                                const gchar *new,
                                GCancellable *cancellable,
                                GError **error)
{
	CamelLocalFolder *folder;
	CamelLocalSettings *local_settings;
	CamelSettings *settings;
	CamelService *service;
	gchar *old_basename;
	gchar *new_basename;
	gchar *newibex;
	gchar *oldibex;
	gchar *path;
	gboolean success = TRUE;

	service = CAMEL_SERVICE (store);

	settings = camel_service_ref_settings (service);

	local_settings = CAMEL_LOCAL_SETTINGS (settings);
	path = camel_local_settings_dup_path (local_settings);

	g_object_unref (settings);

	old_basename = g_strdup_printf ("%s.ibex", old);
	new_basename = g_strdup_printf ("%s.ibex", new);

	oldibex = g_build_filename (path, old_basename, NULL);
	newibex = g_build_filename (path, new_basename, NULL);

	g_free (old_basename);
	g_free (new_basename);


	d (printf ("local rename folder '%s' '%s'\n", old, new));

	folder = camel_object_bag_get (store->folders, old);
	if (folder && folder->index) {
		if (camel_index_rename (folder->index, newibex) == -1)
			goto ibex_failed;
	} else {


		if (camel_text_index_rename (oldibex, newibex) == -1)
			goto ibex_failed;
	}

	if (xrename (old, new, path, ".ev-summary", TRUE, error))
		goto summary_failed;

	if (xrename (old, new, path, ".ev-summary-meta", TRUE, error))
		goto summary_failed;

	if (xrename (old, new, path, ".cmeta", TRUE, error))
		goto cmeta_failed;

	if (xrename (old, new, path, "", FALSE, error))
		goto base_failed;

	g_free (newibex);
	g_free (oldibex);

	if (folder)
		g_object_unref (folder);

	goto exit;


base_failed:
	xrename (new, old, path, ".cmeta", TRUE, NULL);

cmeta_failed:
	xrename (new, old, path, ".ev-summary", TRUE, NULL);
	xrename (new, old, path, ".ev-summary-meta", TRUE, NULL);
summary_failed:
	if (folder) {
		if (folder->index)
			camel_index_rename (folder->index, oldibex);
	} else
		camel_text_index_rename (newibex, oldibex);
ibex_failed:
	g_set_error (
		error, G_IO_ERROR,
		g_io_error_from_errno (errno),
		_("Could not rename '%s': %s"),
		old, g_strerror (errno));

	g_free (newibex);
	g_free (oldibex);

	if (folder)
		g_object_unref (folder);

	success = FALSE;

exit:
	g_free (path);

	return success;
}
