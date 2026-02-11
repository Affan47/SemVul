gnumeric_proper (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	char const *p;
	GString    *res    = g_string_new (NULL);
	gboolean   inword = FALSE;

	p = value_peek_string (argv[0]);
	while (*p) {
		gunichar uc = g_utf8_get_char (p);

		if (g_unichar_isalpha (uc)) {
			if (inword) {
				g_string_append_unichar
					(res, g_unichar_tolower (uc));
			} else {
				g_string_append_unichar
					(res, g_unichar_toupper (uc));
				inword = TRUE;
			}
		} else {
			g_string_append_unichar (res, uc);
			inword = FALSE;
		}

		p = g_utf8_next_char (p);
	}

	return value_new_string_nocopy (g_string_free (res, FALSE));
}
