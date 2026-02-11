emit_change_signals_for_all_files (NemoDirectory *directory)
{
	GList *files;

	files = g_list_copy (directory->details->file_list);
	if (directory->details->as_file != NULL) {
		files = g_list_prepend (files, directory->details->as_file);
	}

	nemo_file_list_ref (files);
	nemo_directory_emit_change_signals (directory, files);

	nemo_file_list_free (files);
}
