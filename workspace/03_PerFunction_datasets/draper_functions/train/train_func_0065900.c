incremental_find_check_match (IncrementalFind *handle, WIN32_FIND_DATA *data, MonoString **result)
{
	gchar *utf8_result;
	gchar *full_name;

	if ((data->cFileName[0] == '.' && data->cFileName[1] == 0) || (data->cFileName[0] == '.' && data->cFileName[1] == '.' && data->cFileName[2] == 0))
		return FALSE;

	utf8_result = g_utf16_to_utf8 (data->cFileName, -1, NULL, NULL, NULL);
	if (utf8_result == NULL)
		return FALSE;

	full_name = g_build_filename (handle->utf8_path, utf8_result, NULL);
	g_free (utf8_result);
	*result = mono_string_new (mono_domain_get (), full_name);
	g_free (full_name);

	return TRUE;
}
