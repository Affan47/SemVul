procmime_mimeparser_register(MimeParser *parser)
{
	if (!procmime_get_mimeparser_for_type(parser->type, parser->sub_type))
		registered_parsers = g_slist_append(registered_parsers, parser);
}
