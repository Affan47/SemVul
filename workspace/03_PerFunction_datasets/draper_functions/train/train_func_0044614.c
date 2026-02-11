tracker_merge_const (const gchar *delimiter,
                     gint         n_values,
                     ...)
{
	va_list args;
	gint    i;
	GString *str = NULL;

	va_start (args, n_values);

	for (i = 0; i < n_values; i++) {
		gchar *value;

		value = va_arg (args, gchar *);
		if (value) {
			if (!str) {
				str = g_string_new (value);
			} else {
				if (delimiter) {
					g_string_append (str, delimiter);
				}
				g_string_append (str, value);
			}
		}
	}

	va_end (args);

	if (!str) {
		return NULL;
	}

	return g_string_free (str, FALSE);
}
