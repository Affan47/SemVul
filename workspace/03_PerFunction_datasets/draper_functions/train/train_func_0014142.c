project_filter_c(const gchar *file)
{
	if (filetypes_detect_from_file(file)->id == GEANY_FILETYPES_C)
		return TRUE;
	return FALSE;
}
