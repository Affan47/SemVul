_g_key_file_save_to_uri (GKeyFile *key_file,
			 const char *uri,
			 GError  **error)
{
	GFile *file;
	char *data;
	gsize len;

	data = g_key_file_to_data (key_file, &len, error);
	if (data == NULL) {
		return FALSE;
	}
	file = g_file_new_for_uri (uri);
	if (!g_file_replace_contents (file,
				      data, len,
				      NULL, FALSE,
				      G_FILE_CREATE_NONE,
				      NULL, NULL, error)) {
		g_object_unref (file);
		g_free (data);
		return FALSE;
	}
	g_object_unref (file);
	g_free (data);
	return TRUE;
}
