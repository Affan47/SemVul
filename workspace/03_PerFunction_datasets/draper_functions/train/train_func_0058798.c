parseExport (tokenInfo *const token)
{
	token->isExported = TRUE;
	readToken (token);
	if (isType (token, TOKEN_OPEN_BRACE))
	{
		token->isExported = FALSE;
		while (! isType (token, TOKEN_CLOSE_BRACE))
		{
			if (isType (token, TOKEN_IDENTIFIER))
				token->isExported |= !isIdentifierMatch (token, "NONE");
			readToken (token);
		}
		readToken (token);
	}
}
