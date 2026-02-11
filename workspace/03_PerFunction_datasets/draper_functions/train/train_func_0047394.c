local_store_get_folder_sync (CamelStore *store,
                             const gchar *folder_name,
                             CamelStoreGetFolderFlags flags,
                             GCancellable *cancellable,
                             GError **error)
{
	CamelLocalSettings *local_settings;
	CamelSettings *settings;
	CamelService *service;
	CamelFolder *folder = NULL;
	struct stat st;
	gchar *path;

	service = CAMEL_SERVICE (store);

	settings= camel_service_ref_settings (service);

	local_settings = CAMEL_LOCAL_SETTINGS (settings);
	path = camel_local_settings_dup_path (local_settings);

	g_object_unref (settings);

	if (!g_path_is_absolute (path)) {
		g_set_error (
			error, CAMEL_STORE_ERROR,
			CAMEL_STORE_ERROR_NO_FOLDER,
			_("Store root %s is not an absolute path"), path);
		goto exit;
	}

	if (g_stat (path, &st) == 0) {
		if (!S_ISDIR (st.st_mode)) {
			g_set_error (
				error, CAMEL_STORE_ERROR,
				CAMEL_STORE_ERROR_NO_FOLDER,
				_("Store root %s is not a regular directory"), path);
			return NULL;
		}
		folder = (CamelFolder *) 0xdeadbeef;
		goto exit;
	}

	if (errno != ENOENT
	    || (flags & CAMEL_STORE_FOLDER_CREATE) == 0) {
		g_set_error (
			error, G_IO_ERROR,
			g_io_error_from_errno (errno),
			_("Cannot get folder: %s: %s"),
			path, g_strerror (errno));
		goto exit;
	}


	if (g_mkdir_with_parents (path, 0700) == -1 && errno != EEXIST) {
		g_set_error (
			error, G_IO_ERROR,
			g_io_error_from_errno (errno),
			_("Cannot get folder: %s: %s"),
			path, g_strerror (errno));
		goto exit;
	}

	folder = (CamelFolder *) 0xdeadbeef;

exit:
	g_free (path);

	return folder;
}
