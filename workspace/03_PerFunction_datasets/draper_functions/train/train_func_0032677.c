camel_pop3_folder_new (CamelStore *parent,
                       GCancellable *cancellable,
                       GError **error)
{
	CamelFolder *folder;
	CamelService *service;
	CamelSettings *settings;
	CamelPOP3Folder *pop3_folder;

	service = CAMEL_SERVICE (parent);

	d (printf ("opening pop3 INBOX folder\n"));

	folder = g_object_new (
		CAMEL_TYPE_POP3_FOLDER,
		"full-name", "inbox", "display-name", "inbox",
		"parent-store", parent, NULL);

	settings = camel_service_ref_settings (service);

	pop3_folder = (CamelPOP3Folder *) folder;
	pop3_folder->mobile_mode = camel_pop3_settings_get_mobile_mode (
		CAMEL_POP3_SETTINGS (settings));

	g_object_unref (settings);

	pop3_folder->fetch_more = 0;
	if (pop3_folder->mobile_mode) {

		gchar *path;
		const gchar *root;

		pop3_folder->key_file = g_key_file_new ();
		root = camel_service_get_user_cache_dir (service);
		path = g_build_filename (root, "uidconfig", NULL);
		g_key_file_load_from_file (pop3_folder->key_file, path, G_KEY_FILE_NONE, NULL);

		g_free (path);
	}

	if (camel_service_get_connection_status (CAMEL_SERVICE (parent)) != CAMEL_SERVICE_CONNECTED)
		return folder;


	if (!camel_folder_refresh_info_sync (folder, cancellable, error)) {
		g_object_unref (folder);
		folder = NULL;
	}

	return folder;
}
