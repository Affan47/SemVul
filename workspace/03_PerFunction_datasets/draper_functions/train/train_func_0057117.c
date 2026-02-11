check_file_is_directory (GFile *file, GError **error)
{
	GFileInfo *info;

	info = g_file_query_info (file, G_FILE_ATTRIBUTE_STANDARD_TYPE, G_FILE_QUERY_INFO_NONE, NULL, error);
	if (*error == NULL) {

		GFileType filetype;
		gboolean ret = TRUE;

		filetype = g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_STANDARD_TYPE);
		if (filetype != G_FILE_TYPE_DIRECTORY) {

			ret = FALSE;
		}

		g_object_unref (info);
		return ret;
	}

	if (g_error_matches (*error, G_IO_ERROR, G_IO_ERROR_NOT_FOUND)) {
		g_clear_error (error);
	}
	return FALSE;
}
