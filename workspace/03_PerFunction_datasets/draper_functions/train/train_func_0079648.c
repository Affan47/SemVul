desktop_directory_file_get_deep_counts (NautilusFile *file,
					guint *directory_count,
					guint *file_count,
					guint *unreadable_directory_count,
					goffset *total_size)
{
	NautilusDesktopDirectoryFile *desktop_file;
	NautilusRequestStatus status;

	desktop_file = NAUTILUS_DESKTOP_DIRECTORY_FILE (file);

	status = nautilus_file_get_deep_counts (desktop_file->details->real_dir_file,
						directory_count,
						file_count,
						unreadable_directory_count,
						total_size,
						TRUE);

	if (file_count) {
		*file_count += g_list_length (file->details->directory->details->file_list);
	}

	return status;
}
