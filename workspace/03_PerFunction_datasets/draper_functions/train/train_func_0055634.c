_g_file_get_mime_type (GFile    *file,
                       gboolean  fast_file_type)
{
	GFileInfo  *info;
	GError     *error = NULL;
 	const char *result = NULL;

 	info = g_file_query_info (file,
				  (fast_file_type ?
				   G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE :
				   G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE),
				  0,
				  NULL,
				  &error);
	if (info == NULL) {
		g_warning ("%s", error->message);
		g_clear_error (&error);
	}
	else {
		result = _g_str_get_static (g_file_info_get_content_type (info));
		g_object_unref (info);
	}

	return result;
}
