parse_attributes (GBytes *data)
{
	GcrParser *parser;
	GckAttributes *attrs = NULL;
	GError *error = NULL;

	parser = gcr_parser_new ();
	g_signal_connect (parser, "parsed", G_CALLBACK (on_parser_parsed), &attrs);
	gcr_parser_parse_data (parser, g_bytes_get_data (data, NULL),
	                       g_bytes_get_size (data), &error);
	g_assert_no_error (error);
	g_object_unref (parser);

	g_assert (attrs);
	return attrs;
}
