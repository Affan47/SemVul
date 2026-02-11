parcel_initToken(ParcelParser *parser, ParcelToken *tokens, intmax_t tokenNum)
{
	if (parser->toknext >= tokenNum) return NULL;
	ParcelToken *tok = &tokens[parser->toknext++];
	tok->start = tok->end = -1;
	tok->size = 0;
	tok->parent = -1;
	return tok;
}
