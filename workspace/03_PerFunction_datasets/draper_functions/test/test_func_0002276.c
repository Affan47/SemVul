migrate_parse_gconf_xml (ParseType parse_type,
                         const gchar *contents,
                         gsize length,
                         GError **error)
{
	GMarkupParseContext *context;
	ParseData *parse_data;
	gboolean success = FALSE;

	parse_data = parse_data_new (parse_type);

	context = g_markup_parse_context_new (
		&gconf_xml_parser, 0, parse_data,
		(GDestroyNotify) parse_data_free);

	if (g_markup_parse_context_parse (context, contents, length, error))
		if (g_markup_parse_context_end_parse (context, error))
			success = TRUE;

	g_markup_parse_context_free (context);

	return success;
}
