json_parser_free(json_parser *parser)
{
	if (!parser)
		return 0;
	free(parser->stack);
	free(parser->buffer);
	parser->stack = NULL;
	parser->buffer = NULL;
	return 0;
}
