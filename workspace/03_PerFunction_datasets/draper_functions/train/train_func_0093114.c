camel_nntp_store_summary_path_to_full (CamelNNTPStoreSummary *s,
                                       const gchar *path,
                                       gchar dir_sep)
{
	gchar *full, *f;
	guint32 c, v = 0;
	const gchar *p;
	gint state = 0;
	gchar *subpath, *last = NULL;
	gsize subpath_len = 0;
	CamelStoreInfo *si;


	subpath_len = strlen (path) + 1;
	subpath = g_alloca (subpath_len);
	g_strlcpy (subpath, path, subpath_len);
	do {
		si = camel_store_summary_path ((CamelStoreSummary *) s, subpath);
		if (si == NULL) {
			last = strrchr (subpath, '/');
			if (last)
				*last = 0;
		}
	} while (si == NULL && last);


	if (si && strlen (subpath) == strlen (path)) {
		f = g_strdup (((CamelNNTPStoreInfo *) si)->full_name);
		camel_store_summary_info_unref ((CamelStoreSummary *) s, si);
		return f;
	}

	f = full = g_alloca (strlen (path) * 2 + 1);
	if (si)
		p = path + strlen (subpath);
	else
		p = path;

	while ((c = camel_utf8_getc ((const guchar **) &p))) {
		switch (state) {
		case 0:
			if (c == '%') {
				state = 1;
			} else {
				if (c == '/')
					c = dir_sep;
				camel_utf8_putc ((guchar **) &f, c);
			}
			break;
		case 1:
			state = 2;
			v = hexnib (c) << 4;
			break;
		case 2:
			state = 0;
			v |= hexnib (c);
			camel_utf8_putc ((guchar **) &f, v);
			break;
		}
	}
	camel_utf8_putc ((guchar **) &f, c);


	f = camel_utf8_utf7 (full);
	if (si) {
		full = g_strdup_printf ("%s%s", ((CamelNNTPStoreInfo *) si)->full_name, f);
		g_free (f);
		camel_store_summary_info_unref ((CamelStoreSummary *) s, si);
		f = full;
	}

	return f;
}
