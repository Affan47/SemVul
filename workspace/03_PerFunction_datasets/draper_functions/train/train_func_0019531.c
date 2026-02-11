rssyl_create_folder(Folder *folder,
								FolderItem *parent, const gchar *name)
{
	gchar *path = NULL, *tmp;
	FolderItem *newitem = NULL;

	g_return_val_if_fail(folder != NULL, NULL);
	g_return_val_if_fail(parent != NULL, NULL);
	g_return_val_if_fail(name != NULL, NULL);
	tmp = rssyl_feed_title_to_dir((gchar *)name);
	path = g_strconcat((parent->path != NULL) ? parent->path : "", ".",
				tmp, NULL);
	g_free(tmp);
	newitem = folder_item_new(folder, name, path);
	folder_item_append(parent, newitem);
	g_free(path);

	return newitem;
}
