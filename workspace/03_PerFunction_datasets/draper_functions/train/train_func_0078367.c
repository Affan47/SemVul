clear_stray_NULs (GOIOContext *context, GString *utf8data)
{
	char *cpointer, *endpointer;
	int null_chars = 0;

	cpointer = utf8data->str;
	endpointer = utf8data->str + utf8data->len;
	while (*cpointer != 0)
		cpointer++;
	while (cpointer != endpointer) {
		null_chars++;
		*cpointer = ' ';
		while (*cpointer != 0)
			cpointer++;
	}
	if (null_chars > 0) {
		gchar const *format;
		gchar *msg;
		format = ngettext ("The file contains %d NULL character. "
				   "It has been changed to a space.",
				   "The file contains %d NULL characters. "
				   "They have been changed to spaces.",
				   null_chars);
		msg = g_strdup_printf (format, null_chars);
		stf_warning (context, msg);
		g_free (msg);
	}
}
