vfs_file_get_deep_counts (NautilusFile *file,
			  guint *directory_count,
			  guint *file_count,
			  guint *unreadable_directory_count,
			  goffset *total_size)
{
	GFileType type;

	if (directory_count != NULL) {
		*directory_count = 0;
	}
	if (file_count != NULL) {
		*file_count = 0;
	}
	if (unreadable_directory_count != NULL) {
		*unreadable_directory_count = 0;
	}
	if (total_size != NULL) {
		*total_size = 0;
	}

	if (!nautilus_file_is_directory (file)) {
		return NAUTILUS_REQUEST_DONE;
	}

	if (file->details->deep_counts_status != NAUTILUS_REQUEST_NOT_STARTED) {
		if (directory_count != NULL) {
			*directory_count = file->details->deep_directory_count;
		}
		if (file_count != NULL) {
			*file_count = file->details->deep_file_count;
		}
		if (unreadable_directory_count != NULL) {
			*unreadable_directory_count = file->details->deep_unreadable_count;
		}
		if (total_size != NULL) {
			*total_size = file->details->deep_size;
		}
		return file->details->deep_counts_status;
	}


	type = nautilus_file_get_file_type (file);
	if (type == G_FILE_TYPE_UNKNOWN
	    || type == G_FILE_TYPE_DIRECTORY) {
		return NAUTILUS_REQUEST_NOT_STARTED;
	}


	return NAUTILUS_REQUEST_DONE;
}
