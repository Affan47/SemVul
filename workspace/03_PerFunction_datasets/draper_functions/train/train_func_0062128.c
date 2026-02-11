autocorrect_first_letter (const char *src)
{
	const char * last_end = NULL;
	const char *last_copy = src;
	const char *this;
	GString *gstr = NULL;
	gboolean seen_text = FALSE;
	gboolean seen_white = FALSE;

	for (this = src; '\0' != *this; this = g_utf8_next_char (this)) {
		gunichar this_char = g_utf8_get_char (this);

		seen_text = seen_text || g_unichar_isalpha (this_char);

		if (seen_text && autocorrect_first_letter_trigger (this_char))
			last_end = this;
		else if ((last_end != NULL) && g_unichar_isspace (this_char))
			seen_white = TRUE;
		else if ((last_end != NULL) && !g_unichar_isspace (this_char)) {
			if (seen_white) {
				gunichar new = g_unichar_totitle (this_char);

				if ((this_char != new) &&
				    !autocorrect_first_letter_exception (src, last_end)) {
					if (gstr == NULL)
						gstr = g_string_new (NULL);
					g_string_append_len (gstr, last_copy,
							     this - last_copy);
					g_string_append_unichar (gstr, new);
					last_copy = g_utf8_next_char (this);
				}
				seen_white = FALSE;
			}
			last_end = NULL;
		}
	}

	if (gstr != NULL) {
		g_string_append_len (gstr, last_copy,
				     strlen (last_copy));
		return g_string_free (gstr, FALSE);
	}

	return NULL;
}
