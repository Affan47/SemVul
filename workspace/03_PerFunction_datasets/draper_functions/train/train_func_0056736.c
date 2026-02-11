e_utf8_to_charset_string_sized (const gchar *charset,
                                const gchar *string,
                                gint bytes)
{
	iconv_t ic;
	gchar *ret;

	if (!string) return NULL;

	ic = camel_iconv_open (charset, "utf-8");
	ret = e_utf8_to_iconv_string_sized (ic, string, bytes);
	camel_iconv_close (ic);

	return ret;
}
