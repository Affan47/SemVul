_g_file_get_mime_type (GFile    *file,
		       gboolean  fast_file_type)
{
	GFileInfo  *info;
	GError     *err = NULL;
 	const char *result = NULL;

	info = g_file_query_info (file,
				  fast_file_type ?
				  G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE :
				  G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE,
				  0, NULL, &err);
	if (info == NULL) {
		char *uri;

		uri = g_file_get_uri (file);
		g_warning ("could not get content type for %s: %s", uri, err->message);
		g_free (uri);
		g_clear_error (&err);
	}
	else {
		result = get_static_string (g_content_type_get_mime_type (g_file_info_get_content_type (info)));
		g_object_unref (info);
	}

	return result;
}
