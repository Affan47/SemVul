set_content_foo (SoupMessageHeaders *hdrs, const char *header_name,
		 const char *foo, GHashTable *params)
{
	GString *str;
	GHashTableIter iter;
	gpointer key, value;

	str = g_string_new (foo);
	if (params) {
		g_hash_table_iter_init (&iter, params);
		while (g_hash_table_iter_next (&iter, &key, &value)) {
			g_string_append (str, "; ");
			soup_header_g_string_append_param (str, key, value);
		}
	}

	soup_message_headers_replace (hdrs, header_name, str->str);
	g_string_free (str, TRUE);
}
