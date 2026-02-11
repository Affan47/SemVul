IoMessage_parseArgs(IoMessage *self, IoLexer *lexer)
{
	IoLexer_pop(lexer);

	if (IoTokenType_isValidMessageName(IoLexer_topType(lexer)))
	{
		IoMessage *arg = IoMessage_newParseNextMessageChain(IOSTATE, lexer);
		IoMessage_addArg_(self, arg);

		while (IoLexer_topType(lexer) == COMMA_TOKEN)
		{
			IoLexer_pop(lexer);

			if (IoTokenType_isValidMessageName(IoLexer_topType(lexer)))
			{
				IoMessage *arg = IoMessage_newParseNextMessageChain(IOSTATE, lexer);
				IoMessage_addArg_(self, arg);
			}


			else
			{

			}
		}
	}

	if (IoLexer_topType(lexer) != CLOSEPAREN_TOKEN)
	{

	}
	IoLexer_pop(lexer);
}
