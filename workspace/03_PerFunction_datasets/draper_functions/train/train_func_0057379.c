format_internal (const gchar *key,
                 DTFormatKind kind,
                 time_t tvalue,
                 struct tm *tm_value)
{
	const gchar *fmt;
	gchar buff[129];
	GString *use_fmt = NULL;
	gint i, last = 0;
	struct tm today, value;
	time_t ttoday;

	tzset ();
	if (!tm_value) {
		localtime_r (&tvalue, &value);
		tm_value = &value;
	} else {

		tvalue = mktime (tm_value);
		localtime_r (&tvalue, &value);
	}

	fmt = get_format_internal (key, kind);
	for (i = 0; fmt[i]; i++) {
		if (fmt[i] == '%') {
			if (fmt[i + 1] == '%') {
				i++;
			} else if (fmt[i + 1] == 'a' && fmt[i + 2] == 'd' && (fmt[i + 3] == 0 || !g_ascii_isalpha (fmt[i + 3]))) {
				gchar *ad;


				if (!use_fmt) {
					use_fmt = g_string_new ("");

					ttoday = time (NULL);
					localtime_r (&ttoday, &today);
				}

				g_string_append_len (use_fmt, fmt + last, i - last);
				last = i + 3;
				i += 2;

				ad = format_relative_date (tvalue, ttoday, &value, &today);
				if (ad)
					g_string_append (use_fmt, ad);
				else if (g_ascii_isspace (fmt[i + 3]))
					i++;

				g_free (ad);
			}
		}
	}

	if (use_fmt && last < i) {
		g_string_append_len (use_fmt, fmt + last, i - last);
	}

	e_utf8_strftime_fix_am_pm (buff, sizeof (buff) - 1, use_fmt ? use_fmt->str : fmt, tm_value);

	if (use_fmt)
		g_string_free (use_fmt, TRUE);

	return g_strstrip (g_strdup (buff));
}
