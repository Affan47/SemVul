tracker_file_is_hidden (GFile *file)
{
	GFileInfo *file_info;
	gboolean is_hidden = FALSE;

	file_info = g_file_query_info (file,
	                               G_FILE_ATTRIBUTE_STANDARD_IS_HIDDEN,
	                               G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
	                               NULL, NULL);
	if (file_info) {

		is_hidden = g_file_info_get_is_hidden (file_info);
		g_object_unref (file_info);
	}

	return is_hidden;
}
