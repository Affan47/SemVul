filename_to_utf8_normalized(const char *src, uni_norm_t norm)
{
	const GSList *sl;
	const char *s = NULL;
	char *dbuf = NULL, *dst;

	g_assert(src);

	for (sl = sl_filename_charsets; sl != NULL; sl = g_slist_next(sl)) {
		const struct conv_to_utf8 *t = sl->data;

		conv_to_utf8_check(t);

		if (t->is_utf8)	{
			if (utf8_is_valid_string(src)) {
				s = src;
				break;
			}
		} else if (t->is_ascii) {
			if (is_ascii_string(src)) {
				s = src;
				break;
			}
		} else if (t->is_iso8859) {


			if (!iso8859_is_valid_string(src))
				continue;
			if (is_ascii_string(src)) {
				s = src;
				break;
			}
		}

		dbuf = hyper_iconv(t->cd, NULL, 0, src, (size_t) -1, TRUE);
		if (dbuf) {
			s = dbuf;
			break;
		}
	}

	if (!s) {
		if (!utf8_is_valid_string(src)) {
			g_warning("Could not properly convert to UTF-8: \"%s\"", src);
		}
		g_assert(NULL == dbuf);
		dbuf = hyper_utf8_enforce(NULL, 0, src, (size_t) -1);
		s = dbuf;
	}

	dst = utf8_normalize(s, norm);
	if (dbuf != dst) {
		G_FREE_NULL(dbuf);
	}
	return dst;
}
