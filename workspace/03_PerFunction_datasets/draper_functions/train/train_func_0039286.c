mh_fetch_msg(Folder *folder, FolderItem *item, gint num)
{
	gchar *path;
	gchar *file;

	cm_return_val_if_fail(item != NULL, NULL);
	cm_return_val_if_fail(num > 0, NULL);

	path = folder_item_get_path(item);
	file = g_strconcat(path, G_DIR_SEPARATOR_S, itos(num), NULL);

	if (!is_file_exist(file)) {
		g_free(file);
		g_free(path);
		return NULL;
	}
	g_free(path);
	return file;
}
