text_from_time(time_t t)
{
	static gchar *ret = NULL;
	gchar buf[128];
	gint buflen;
	struct tm *btime;
	GError *error = NULL;

	btime = localtime(&t);


	buflen = strftime(buf, sizeof(buf), "%x %X", btime);
	if (buflen < 1) return "";

	g_free(ret);
	ret = g_locale_to_utf8(buf, buflen, NULL, NULL, &error);
	if (error)
		{
		log_printf("Error converting locale strftime to UTF-8: %s\n", error->message);
		g_error_free(error);
		return "";
		}

	return ret;
}
