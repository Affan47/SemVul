procmime_get_mimeparser_for_type(MimeMediaType type, const gchar *sub_type)
{
	GSList *cur;
	for (cur = registered_parsers; cur; cur = cur->next) {
		MimeParser *parser = (MimeParser *)cur->data;
		if (parser->type == type && !strcmp2(parser->sub_type, sub_type))
			return parser;
	}
	return NULL;
}
