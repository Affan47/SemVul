file_is_in_subfolder_of (const char *filename,
		         GList      *folder_list)
{
	GList *scan;

	if (filename == NULL)
		return FALSE;

	for (scan = folder_list; scan; scan = scan->next) {
		char *folder_in_list = (char*) scan->data;

		if (_g_path_is_parent_of (folder_in_list, filename))
			return TRUE;
	}

	return FALSE;
}
