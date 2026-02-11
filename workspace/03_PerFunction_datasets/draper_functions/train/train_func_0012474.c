_sgmlParserAppendBuffer(SGML_PARSER *parser, const char *chunk, unsigned long startOffset, unsigned long endOffset)
{
	unsigned long copyLength = endOffset - startOffset;
	char *saveBuf = NULL;

	if (endOffset <= startOffset)
		return;

	if (!parser->internal.currentBuffer)
		parser->internal.currentBuffer = (char *)malloc(copyLength + 1);
	else
		parser->internal.currentBuffer = (char *)realloc((saveBuf = parser->internal.currentBuffer), parser->internal.currentBufferSize + copyLength + 1);

	if (!parser->internal.currentBuffer)
	{
		if (saveBuf)
			free(saveBuf);
	}
	else
		memcpy(parser->internal.currentBuffer + parser->internal.currentBufferSize, chunk + startOffset, copyLength);

	parser->internal.currentBufferSize += copyLength;
}
