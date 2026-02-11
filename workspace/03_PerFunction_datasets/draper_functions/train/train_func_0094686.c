eog_util_make_valid_utf8 (const gchar *str)
{
	GString *string;
	const char *remainder, *invalid;
	int remaining_bytes, valid_bytes;

	string = NULL;
	remainder = str;
	remaining_bytes = strlen (str);

	while (remaining_bytes != 0) {
		if (g_utf8_validate (remainder, remaining_bytes, &invalid)) {
			break;
		}

		valid_bytes = invalid - remainder;

		if (string == NULL) {
			string = g_string_sized_new (remaining_bytes);
		}

		g_string_append_len (string, remainder, valid_bytes);
		g_string_append_c (string, '?');

		remaining_bytes -= valid_bytes + 1;
		remainder = invalid + 1;
	}

	if (string == NULL) {
		return g_strdup (str);
	}

	g_string_append (string, remainder);
	g_string_append (string, _(" (invalid Unicode)"));

	g_assert (g_utf8_validate (string->str, -1, NULL));

	return g_string_free (string, FALSE);
}
