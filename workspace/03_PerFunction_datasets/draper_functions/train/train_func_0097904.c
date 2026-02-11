get_filesystem_entries (const gunichar2 *path,
						 const gunichar2 *path_with_pattern,
						 gint attrs, gint mask,
						 gint32 *error)
{
	int i;
	WIN32_FIND_DATA data;
	HANDLE find_handle;
	GPtrArray *names = NULL;
	gchar *utf8_path = NULL, *utf8_result, *full_name;
	gint32 attributes;

	mask = convert_attrs ((MonoFileAttributes)mask);
	attributes = get_file_attributes (path);
	if (attributes != -1) {
		if ((attributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
			*error = ERROR_INVALID_NAME;
			goto fail;
		}
	} else {
		*error = GetLastError ();
		goto fail;
	}

	find_handle = FindFirstFile (path_with_pattern, &data);
	if (find_handle == INVALID_HANDLE_VALUE) {
		gint32 find_error = GetLastError ();

		if (find_error == ERROR_FILE_NOT_FOUND || find_error == ERROR_NO_MORE_FILES) {

			goto fail;
		}

		*error = find_error;
		goto fail;
	}

	utf8_path = get_search_dir (path_with_pattern);
	names = g_ptr_array_new ();

	do {
		if ((data.cFileName[0] == '.' && data.cFileName[1] == 0) ||
		    (data.cFileName[0] == '.' && data.cFileName[1] == '.' && data.cFileName[2] == 0)) {
			continue;
		}

		if ((data.dwFileAttributes & mask) == attrs) {
			utf8_result = g_utf16_to_utf8 (data.cFileName, -1, NULL, NULL, NULL);
			if (utf8_result == NULL) {
				continue;
			}

			full_name = g_build_filename (utf8_path, utf8_result, NULL);
			g_ptr_array_add (names, full_name);

			g_free (utf8_result);
		}
	} while(FindNextFile (find_handle, &data));

	if (FindClose (find_handle) == FALSE) {
		*error = GetLastError ();
		goto fail;
	}

	g_free (utf8_path);
	return names;
fail:
	if (names) {
		for (i = 0; i < names->len; i++)
			g_free (g_ptr_array_index (names, i));
		g_ptr_array_free (names, TRUE);
	}
	g_free (utf8_path);
	return FALSE;
}
