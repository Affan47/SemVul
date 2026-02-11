camel_content_type_decode (const gchar *in)
{
	const gchar *inptr = in;
	gchar *type, *subtype = NULL;
	CamelContentType *t = NULL;

	if (in == NULL)
		return NULL;

	type = decode_token (&inptr);
	header_decode_lwsp (&inptr);
	if (type) {
		if  (*inptr == '/') {
			inptr++;
			subtype = decode_token (&inptr);
		}
		if (subtype == NULL && (!g_ascii_strcasecmp (type, "text"))) {
			w (g_warning ("text type with no subtype, resorting to text/plain: %s", in));
			subtype = g_strdup ("plain");
		}
		if (subtype == NULL) {
			w (g_warning ("MIME type with no subtype: %s", in));
		}

		t = camel_content_type_new (type, subtype);
		t->params = header_decode_param_list (&inptr);
		g_free (type);
		g_free (subtype);
	} else {
		g_free (type);
		d (printf ("cannot find MIME type in header (2) '%s'", in));
	}
	return t;
}
