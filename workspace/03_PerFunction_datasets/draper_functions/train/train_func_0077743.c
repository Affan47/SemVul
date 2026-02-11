resolve_pattern (xmmsc_connection_t *conn, const gchar *original_pattern,
                 GList **matches)
{
	gboolean match_found = FALSE;
	const gchar *ptr;
	gchar *directory, *pattern;
	GPatternSpec *spec;
	xmmsc_result_t *res;
	xmmsv_t *value;
	xmmsv_list_iter_t *it;

	pattern = normalize_pattern (original_pattern);


	find_next_pattern (pattern, &ptr);


	spec = build_match_pattern (pattern, ptr);


	directory = find_next_directory (pattern, ptr);

	res = xmmsc_xform_media_browse_encoded (conn, directory);
	xmmsc_result_wait (res);

	g_free (directory);

	value = xmmsc_result_get_value (res);
	xmmsv_get_list_iter (value, &it);

	for (; xmmsv_list_iter_valid (it); xmmsv_list_iter_next (it)) {
		xmmsv_t *entry;
		const gchar *path;
		gint is_directory;

		xmmsv_list_iter_entry (it, &entry);

		xmmsv_dict_entry_get_int (entry, "isdir", &is_directory);
		xmmsv_dict_entry_get_string (entry, "path", &path);

		if (!g_pattern_match_string (spec, path)) {
			continue;
		}


		if (strcmp (path, pattern) == 0) {
			add_match (path, is_directory, matches);
			match_found = TRUE;
		} else {
			gchar *npattern = g_strconcat (path, strchr (ptr, '/'), NULL);
			match_found |= resolve_pattern (conn, npattern, matches);
			g_free (npattern);
		}
	}

	xmmsc_result_unref (res);
	g_pattern_spec_free (spec);
	g_free (pattern);

	return match_found;
}
