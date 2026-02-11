gm_string_skip_till(gchar const **ptr, gchar const *find) {
	gchar const *fptr;
	gunichar check, c;

	while (**ptr != '\0') {
		check = g_utf8_get_char(*ptr);
		fptr = find;

		while (*fptr != '\0') {
			c = g_utf8_get_char(fptr);

			if (check == c) {
				return;
			}

			fptr = g_utf8_next_char(fptr);
		}

		*ptr = g_utf8_next_char(*ptr);
	}
}
