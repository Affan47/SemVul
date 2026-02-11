procheader_date_get_localtime(gchar *dest, gint len, const time_t timer)
{
	struct tm *lt;
	gchar *default_format = "%y/%m/%d(%a) %H:%M";
	gchar *str;
	const gchar *src_codeset, *dest_codeset;
	struct tm buf;

	if (timer > 0)
		lt = localtime_r(&timer, &buf);
	else {
		time_t dummy = 1;
		lt = localtime_r(&dummy, &buf);
	}

	if (prefs_common.date_format)
		fast_strftime(dest, len, prefs_common.date_format, lt);
	else
		fast_strftime(dest, len, default_format, lt);

	if (!g_utf8_validate(dest, -1, NULL)) {
		src_codeset = conv_get_locale_charset_str_no_utf8();
		dest_codeset = CS_UTF_8;
		str = conv_codeset_strdup(dest, src_codeset, dest_codeset);
		if (str) {
			strncpy2(dest, str, len);
			g_free(str);
		}
	}
}
