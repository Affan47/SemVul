doTranslate(const char *ostring, const char *from, const char *to)
{
	char buf[2048];
	char *result;
	char *string;
	AyConnection *fd;
	struct http_data *d = g_new0(struct http_data, 1);

	string = trans_urlencode(ostring);
	snprintf(buf, 2048, "/translate_t?hl=%s&js=n&text=%s&sl=%s&tl=%s",
		from, string, from, to);
	free(string);

	fd = do_http_post("translate.google.com", buf, d);

	if (!fd)
		return NULL;


	d->done = 0;
	d->handle = ay_connection_input_add(fd, EB_INPUT_READ,
		receive_translation, d);
	while (!d->done)
		do_events();

	ay_connection_free(fd);

	if (d->error)
		return NULL;

	eb_debug(DBG_MOD, "Translated %s to %s\n", ostring, d->buf);

	result = g_strdup(d->buf);
	g_free(d);
	return result;
}
