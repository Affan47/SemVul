totem_pl_parser_save_m3u (TotemPlParser    *parser,
                          TotemPlPlaylist  *playlist,
                          GFile            *output,
                          gboolean          dos_compatible,
                          GError          **error)
{
        TotemPlPlaylistIter iter;
	GFileOutputStream *stream;
	gboolean valid, success;
	char *buf;
	const char *cr;

	stream = g_file_replace (output, NULL, FALSE, G_FILE_CREATE_NONE, NULL, error);
	if (stream == NULL)
		return FALSE;

	cr = dos_compatible ? "\r\n" : "\n";

	buf = g_strdup_printf ("#EXTM3U%s", cr);
	success = totem_pl_parser_write_string (G_OUTPUT_STREAM (stream), buf, error);
	g_free (buf);
	if (success == FALSE)
		return FALSE;

        valid = totem_pl_playlist_iter_first (playlist, &iter);

        while (valid) {
		char *uri, *title, *path2;
		GFile *file;

                totem_pl_playlist_get (playlist, &iter,
                                       TOTEM_PL_PARSER_FIELD_URI, &uri,
                                       TOTEM_PL_PARSER_FIELD_TITLE, &title,
                                       NULL);

                valid = totem_pl_playlist_iter_next (playlist, &iter);

                if (!uri) {
                        g_free (title);
                        continue;
                }

                file = g_file_new_for_uri (uri);

		if (totem_pl_parser_scheme_is_ignored (parser, file) != FALSE) {
			g_object_unref (file);
			g_free (uri);
			g_free (title);
			continue;
		}
		g_object_unref (file);

		if (title) {
			buf = g_strdup_printf (EXTINF",%s%s", title, cr);
			success = totem_pl_parser_write_string (G_OUTPUT_STREAM (stream), buf, error);
			g_free (buf);
			if (success == FALSE) {
				g_free (title);
				g_free (uri);
				return FALSE;
			}
		}
		g_free (title);

		if (dos_compatible == FALSE) {
			char *tmp;

			tmp = totem_pl_parser_relative (output, uri);

			if (tmp == NULL && g_str_has_prefix (uri, "file:")) {
				path2 = g_filename_from_uri (uri, NULL, NULL);
			} else {
				path2 = tmp;
			}
		} else {
			path2 = totem_pl_parser_uri_to_dos (uri, output);
		}

		buf = g_strdup_printf ("%s%s", path2 ? path2 : uri, cr);
		g_free (path2);
		g_free (uri);

		success = totem_pl_parser_write_string (G_OUTPUT_STREAM (stream), buf, error);
		g_free (buf);

		if (success == FALSE)
			return FALSE;
	}

	g_object_unref (stream);

	return TRUE;
}
