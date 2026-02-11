i_key_file_to_file (GKeyFile* key_file, gchar const* file, gsize* length, GError** error)
{
	gboolean ret = FALSE;
	gchar* contents;
	gsize len;

	if ((contents = g_key_file_to_data(key_file, &len, error)) != NULL)
	{
		ret = g_file_set_contents(file, contents, len, error);
		g_free(contents);
	}

	if (length != NULL)
	{
		*length = len;
	}

	return ret;
}
