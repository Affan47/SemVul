clear_special_headers (SoupMessageHeaders *hdrs)
{
	SoupHeaderSetter setter;
	GHashTableIter iter;
	gpointer key, value;


	intern_header_name ("", NULL);

	g_hash_table_iter_init (&iter, header_setters);
	while (g_hash_table_iter_next (&iter, &key, &value)) {
		setter = value;
		setter (hdrs, NULL);
	}
}
