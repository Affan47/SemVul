gedit_encoding_get_current (void)
{
	static gboolean initialized = FALSE;
	static const GeditEncoding *locale_encoding = NULL;

	const gchar *locale_charset;

	gedit_encoding_lazy_init ();

	if (initialized != FALSE)
		return locale_encoding;

	if (g_get_charset (&locale_charset) == FALSE)
	{
		g_return_val_if_fail (locale_charset != NULL, &utf8_encoding);

		locale_encoding = gedit_encoding_get_from_charset (locale_charset);
	}
	else
	{
		locale_encoding = &utf8_encoding;
	}

	if (locale_encoding == NULL)
	{
		locale_encoding = &unknown_encoding;
	}

	g_return_val_if_fail (locale_encoding != NULL, NULL);

	initialized = TRUE;

	return locale_encoding;
}
