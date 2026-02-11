tracker_media_art_strip_invalid_entities (const gchar *original)
{
	GString *str_no_blocks;
	gchar **strv;
	gchar *str;
	gboolean blocks_done = FALSE;
	const gchar *p;
	const gchar *invalid_chars = "()[]<>{}_!@#$^&*+=|\\/\"'?~";
	const gchar *invalid_chars_delimiter = "*";
	const gchar *convert_chars = "\t";
	const gchar *convert_chars_delimiter = " ";
	const gunichar blocks[5][2] = {
		{ '(', ')' },
		{ '{', '}' },
		{ '[', ']' },
		{ '<', '>' },
		{  0,   0  }
	};

	str_no_blocks = g_string_new ("");

	p = original;

	while (!blocks_done) {
		gint pos1, pos2, i;

		pos1 = -1;
		pos2 = -1;

		for (i = 0; blocks[i][0] != 0; i++) {
			gint start, end;


			if (media_art_strip_find_next_block (p, blocks[i][0], blocks[i][1], &start, &end)) {
				if (pos1 == -1 || start < pos1) {
					pos1 = start;
					pos2 = end;
				}
			}
		}


		if (pos1 == -1) {

			g_string_append (str_no_blocks, p);
			blocks_done = TRUE;
		} else {

			if (pos1 > 0) {
				g_string_append_len (str_no_blocks, p, pos1);
			}

			p = g_utf8_next_char (p + pos2);


			if (*p == '\0') {
				blocks_done = TRUE;
			}
		}
	}


	str = g_utf8_strdown (str_no_blocks->str, -1);
	g_string_free (str_no_blocks, TRUE);


	g_strdelimit (str, invalid_chars, *invalid_chars_delimiter);
	strv = g_strsplit (str, invalid_chars_delimiter, -1);
	g_free (str);
	str = g_strjoinv (NULL, strv);
	g_strfreev (strv);


	g_strdelimit (str, convert_chars, *convert_chars_delimiter);
	strv = g_strsplit (str, convert_chars_delimiter, -1);
	g_free (str);
	str = g_strjoinv (convert_chars_delimiter, strv);
	g_strfreev (strv);

	while (g_strrstr (str, "  ") != NULL) {

		strv = g_strsplit (str, "  ", -1);
		g_free (str);
		str = g_strjoinv (" ", strv);
		g_strfreev (strv);
	}


	g_strstrip (str);

	return str;
}
