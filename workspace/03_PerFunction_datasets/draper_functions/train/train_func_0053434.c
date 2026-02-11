folder_item_get_tags_file(FolderItem *item)
{
	gchar *path;
	gchar *identifier;
	gchar *file;


	cm_return_val_if_fail(item != NULL, NULL);

	identifier = folder_item_get_identifier(item);
	cm_return_val_if_fail(identifier != NULL, NULL);

#ifdef G_OS_WIN32
	while (strchr(identifier, '/'))
		*strchr(identifier, '/') = '\\';
#endif

	path = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S,
			   "tagsdb", G_DIR_SEPARATOR_S,
			   identifier, NULL);

	g_free(identifier);

	if (!is_dir_exist(path))
		make_dir_hier(path);

	file = g_strconcat(path, G_DIR_SEPARATOR_S, TAGS_FILE, NULL);

	g_free(path);

	return file;
}
