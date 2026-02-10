nemo_file_is_launchable (NemoFile *file)
{
	gboolean type_can_be_executable;

	type_can_be_executable = FALSE;
	if (file->details->mime_type != NULL) {
		type_can_be_executable =
			g_content_type_can_be_executable (eel_ref_str_peek (file->details->mime_type));
	}

	return type_can_be_executable &&
		nemo_file_can_get_permissions (file) &&
		nemo_file_can_execute (file) &&
		nemo_file_is_executable (file) &&
		!nemo_file_is_directory (file);
}
