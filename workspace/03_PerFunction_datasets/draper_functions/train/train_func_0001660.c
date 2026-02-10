IoLexer_readIdentifier(IoLexer *self)
{
	IoLexer_pushPos(self);

	while ( IoLexer_readLetter(self) ||
			IoLexer_readDigit(self) ||
			IoLexer_readSpecialChar(self))
	{}

	if (IoLexer_grabLength(self))
	{


		IoLexer_grabTokenType_(self, IDENTIFIER_TOKEN);
		IoLexer_popPos(self);
		return 1;
	}

	IoLexer_popPosBack(self);

	return 0;
}
