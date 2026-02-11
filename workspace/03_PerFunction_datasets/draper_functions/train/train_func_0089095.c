file_list_contains_files_in_this_dir (GList      *file_list,
				      const char *dirname)
{
	GList *scan;

	for (scan = file_list; scan; scan = scan->next) {
		char *filename = scan->data;

		if (_g_path_is_parent_of (dirname, filename))
			return TRUE;
	}

	return FALSE;
}
