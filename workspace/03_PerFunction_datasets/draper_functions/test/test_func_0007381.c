default_filter_cert (const GtkFileFilterInfo *filter_info, gpointer user_data)
{
	const char *extensions[] = { ".der", ".pem", ".crt", ".cer", NULL };

	if (!filter_info->filename)
		return FALSE;

	if (!file_has_extension (filter_info->filename, extensions))
		return FALSE;

	if (!file_is_der_or_pem (filter_info->filename, FALSE, NULL))
		return FALSE;

	return TRUE;
}
