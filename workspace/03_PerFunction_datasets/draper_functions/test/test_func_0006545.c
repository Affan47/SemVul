desktop_directory_file_check_if_ready (NautilusFile *file,
				       NautilusFileAttributes attributes)
{
	NautilusFileAttributes delegated_attributes, non_delegated_attributes;
	NautilusDesktopDirectoryFile *desktop_file;

	desktop_file = NAUTILUS_DESKTOP_DIRECTORY_FILE (file);

	partition_attributes (attributes,
			      &delegated_attributes,
			      &non_delegated_attributes);

	return real_check_if_ready (file, non_delegated_attributes) &&
		nautilus_file_check_if_ready (desktop_file->details->real_dir_file,
					      delegated_attributes);
}
