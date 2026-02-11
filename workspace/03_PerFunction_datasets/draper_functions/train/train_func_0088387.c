IoLexer_readCharAnyCase_(IoLexer *self, char c)
{
	if (!IoLexer_onNULL(self))
	{
		uchar_t nc = IoLexer_nextChar(self);

		if (nc && tolower(nc) == tolower(c))
		{
			return 1;
		}

		IoLexer_prevChar(self);
	}
	return 0;
}
