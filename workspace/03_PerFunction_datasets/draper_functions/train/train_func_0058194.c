json_parser_free(json_parser *parser)
{
	if (!parser)
		return 0;
	parser_free(parser, parser->stack);
	parser_free(parser, parser->buffer);
	parser->stack = NULL;
	parser->buffer = NULL;
	return 0;
}
