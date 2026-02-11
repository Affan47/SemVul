search_directory_file_get_deep_counts (NautilusFile *file,
				       guint *directory_count,
				       guint *file_count,
				       guint *unreadable_directory_count,
				       goffset *total_size)
{
	NautilusFile *dir_file;
	GList *file_list, *l;
	guint dirs, files;
	GFileType type;

	file_list = nautilus_directory_get_file_list (file->details->directory);

	dirs = files = 0;
	for (l = file_list; l != NULL; l = l->next) {
		dir_file = NAUTILUS_FILE (l->data);
		type = nautilus_file_get_file_type (dir_file);
		if (type == G_FILE_TYPE_DIRECTORY) {
			dirs++;
		} else {
			files++;
		}
	}

	if (directory_count != NULL) {
		*directory_count = dirs;
	}
	if (file_count != NULL) {
		*file_count = files;
	}
	if (unreadable_directory_count != NULL) {
		*unreadable_directory_count = 0;
	}
	if (total_size != NULL) {

		*total_size = 0;
	}

	nautilus_file_list_free (file_list);

	return NAUTILUS_REQUEST_DONE;
}
