filelist_filter(GList *list, gboolean is_dir_list)
{
	GList *work;

	if (!is_dir_list && options->file_filter.disable && options->file_filter.show_hidden_files) return list;

	work = list;
	while (work)
		{
		FileData *fd = (FileData *)(work->data);
		const gchar *name = fd->name;

		if ((!options->file_filter.show_hidden_files && is_hidden_file(name)) ||
		    (!is_dir_list && !filter_name_exists(name)) ||
		    (is_dir_list && name[0] == '.' && (strcmp(name, GQ_CACHE_LOCAL_THUMB) == 0 ||
						       strcmp(name, GQ_CACHE_LOCAL_METADATA) == 0)) )
			{
			GList *link = work;

			list = g_list_remove_link(list, link);
			file_data_unref(fd);
			g_list_free(link);
			}

		work = work->next;
		}

	return list;
}
