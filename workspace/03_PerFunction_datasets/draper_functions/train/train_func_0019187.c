camel_utf7_utf8 (const gchar *ptr)
{
	const guchar *p = (guchar *) ptr;
	guint c;
	guint32 v = 0, x;
	GString *out;
	gint i = 0;
	gint state = 0;
	gchar *ret;

	out = g_string_new ("");
	do {
		c = *p++;
		switch (state) {
		case 0:
			if (c == '&')
				state = 1;
			else
				g_string_append_c (out, c);
			break;
		case 1:
			if (c == '-') {
				g_string_append_c (out, '&');
				state = 0;
			} else if (utf7_rank[c] != 0xff) {
				v = utf7_rank[c];
				i = 6;
				state = 2;
			} else {

				g_string_append (out, "&-");
				state = 0;
			}
			break;
		case 2:
			if (c == '-') {
				state = 0;
			} else if (utf7_rank[c] != 0xff) {
				v = (v << 6) | utf7_rank[c];
				i+=6;
				if (i >= 16) {
					x = (v >> (i - 16)) & 0xffff;
					g_string_append_u (out, x);
					i-=16;
				}
			} else {
				g_string_append_u (out, c);
				state = 0;
			}
			break;
		}
	} while (c);

	ret = g_strdup (out->str);
	g_string_free (out, TRUE);

	return ret;
}
