nemo_file_new_from_filename (NemoDirectory *directory,
				 const char *filename,
				 gboolean self_owned)
{
	NemoFile *file;

	g_assert (NEMO_IS_DIRECTORY (directory));
	g_assert (filename != NULL);
	g_assert (filename[0] != '\0');

	if (NEMO_IS_DESKTOP_DIRECTORY (directory)) {
		if (self_owned) {
			file = NEMO_FILE (g_object_new (NEMO_TYPE_DESKTOP_DIRECTORY_FILE, NULL));
		} else {


			file = NEMO_FILE (g_object_new (NEMO_TYPE_VFS_FILE, NULL));
		}
	} else if (NEMO_IS_SEARCH_DIRECTORY (directory)) {
		if (self_owned) {
			file = NEMO_FILE (g_object_new (NEMO_TYPE_SEARCH_DIRECTORY_FILE, NULL));
		} else {


			file = NEMO_FILE (g_object_new (NEMO_TYPE_VFS_FILE, NULL));
		}
	} else if (g_str_has_suffix (filename, NEMO_SAVED_SEARCH_EXTENSION)) {
		file = NEMO_FILE (g_object_new (NEMO_TYPE_SAVED_SEARCH_FILE, NULL));
	} else {
		file = NEMO_FILE (g_object_new (NEMO_TYPE_VFS_FILE, NULL));
	}

	file->details->directory = nemo_directory_ref (directory);

	file->details->name = eel_ref_str_new (filename);

#ifdef NEMO_FILE_DEBUG_REF
	DEBUG_REF_PRINTF("%10p ref'd", file);
#endif

	return file;
}
