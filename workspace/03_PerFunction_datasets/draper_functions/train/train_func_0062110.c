mbox_store_get_folder_sync (CamelStore *store,
                            const gchar *folder_name,
                            CamelStoreGetFolderFlags flags,
                            GCancellable *cancellable,
                            GError **error)
{
	CamelStoreClass *store_class;
	CamelLocalStore *local_store;
	struct stat st;
	gchar *name;


	store_class = CAMEL_STORE_CLASS (camel_mbox_store_parent_class);
	if (!store_class->get_folder_sync (store, folder_name, flags, cancellable, error))
		return NULL;

	local_store = CAMEL_LOCAL_STORE (store);
	name = camel_local_store_get_full_path (local_store, folder_name);

	if (g_stat (name, &st) == -1) {
		gchar *basename;
		gchar *dirname;
		gint fd;

		if (errno != ENOENT) {
			g_set_error (
				error, G_IO_ERROR,
				g_io_error_from_errno (errno),
				_("Cannot get folder '%s': %s"),
				folder_name, g_strerror (errno));
			g_free (name);
			return NULL;
		}

		if ((flags & CAMEL_STORE_FOLDER_CREATE) == 0) {
			g_set_error (
				error, CAMEL_STORE_ERROR,
				CAMEL_STORE_ERROR_NO_FOLDER,
				_("Cannot get folder '%s': folder does not exist."),
				folder_name);
			g_free (name);
			return NULL;
		}


		basename = g_path_get_basename (folder_name);

		if (basename[0] == '.' || ignore_file (basename, TRUE)) {
			g_set_error (
				error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
				_("Cannot create a folder by this name."));
			g_free (name);
			g_free (basename);
			return NULL;
		}
		g_free (basename);

		dirname = g_path_get_dirname (name);
		if (g_mkdir_with_parents (dirname, 0700) == -1 && errno != EEXIST) {
			g_set_error (
				error, G_IO_ERROR,
				g_io_error_from_errno (errno),
				_("Cannot create folder '%s': %s"),
				folder_name, g_strerror (errno));
			g_free (dirname);
			g_free (name);
			return NULL;
		}

		g_free (dirname);

		fd = g_open (
			name,
			O_LARGEFILE |
			O_WRONLY |
			O_CREAT |
			O_APPEND |
			O_BINARY, 0666);

		if (fd == -1) {
			g_set_error (
				error, G_IO_ERROR,
				g_io_error_from_errno (errno),
				_("Cannot create folder '%s': %s"),
				folder_name, g_strerror (errno));
			g_free (name);
			return NULL;
		}

		g_free (name);
		close (fd);
	} else if (!S_ISREG (st.st_mode)) {
		g_set_error (
			error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
			_("Cannot get folder '%s': not a regular file."),
			folder_name);
		g_free (name);
		return NULL;
	} else if (flags & CAMEL_STORE_FOLDER_EXCL) {
		g_set_error (
			error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
			_("Cannot create folder '%s': folder exists."),
			folder_name);
		g_free (name);
		return NULL;
	} else
		g_free (name);

	return camel_mbox_folder_new (store, folder_name, flags, cancellable, error);
}
