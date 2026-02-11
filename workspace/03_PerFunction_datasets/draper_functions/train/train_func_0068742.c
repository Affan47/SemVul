parseCommonNamelistStmt (tokenInfo *const token, tagType type)
{
	Assert (isKeyword (token, KEYWORD_common) ||
			isKeyword (token, KEYWORD_namelist));
	readToken (token);
	do
	{
		if (isType (token, TOKEN_OPERATOR) &&
			strcmp (vStringValue (token->string), "/") == 0)
		{
			readToken (token);
			if (isType (token, TOKEN_IDENTIFIER))
			{
				makeFortranTag (token, type);
				readToken (token);
			}
			skipPast (token, TOKEN_OPERATOR);
		}
		if (isType (token, TOKEN_IDENTIFIER))
			makeFortranTag (token, TAG_LOCAL);
		readToken (token);
		if (isType (token, TOKEN_PAREN_OPEN))
			skipOverParens (token);
		if (isType (token, TOKEN_COMMA))
			readToken (token);
	} while (! isType (token, TOKEN_STATEMENT_END));
	skipToNextStatement (token);
}
