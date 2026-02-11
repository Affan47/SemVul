locale_init_show_results(void)
{
	const GSList *sl = sl_filename_charsets;

	g_info("language code: \"%s\"", locale_get_language());
	g_info("using locale character set \"%s\"", charset);
	g_info("primary filename character set \"%s\"",
		primary_filename_charset());

	while (NULL != (sl = g_slist_next(sl))) {
		const struct conv_to_utf8 *t = sl->data;

		conv_to_utf8_check(t);
		g_info("additional filename character set \"%s\"", t->name);
	}
}
