bar_sort_collection_list_build(GtkWidget *bookmarks)
{
	FileData *dir_fd;
	GList *list;
	GList *work;

	history_list_free_key(SORT_KEY_COLLECTIONS);
	bookmark_list_set_key(bookmarks, SORT_KEY_COLLECTIONS);

	dir_fd = file_data_new_dir(get_collections_dir());
	filelist_read(dir_fd, &list, NULL);
	file_data_unref(dir_fd);

	list = filelist_sort_path(list);

	work = list;
	while (work)
		{
		FileData *fd;
		gchar *name;

		fd = work->data;
		work = work->next;

		if (file_extension_match(fd->path, GQ_COLLECTION_EXT))
			{
			name = remove_extension_from_path(fd->name);
			}
		else
			{
			name = g_strdup(fd->name);
			}
		bookmark_list_add(bookmarks, name, fd->path);
		g_free(name);
		}

	filelist_free(list);
}
