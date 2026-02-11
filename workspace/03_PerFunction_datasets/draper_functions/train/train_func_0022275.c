parseTable (tokenInfo *const token)
{
	tokenInfo *const name = newToken ();


	readToken (name);
	if (isType (name, TOKEN_OPEN_SQUARE))
	{
		readToken (name);

		readToken (token);
	}
	readToken (token);
	if (isType (token, TOKEN_PERIOD))
	{


		readToken (name);
		if (isType (name, TOKEN_OPEN_SQUARE))
		{
			readToken (name);

			readToken (token);
		}

		if (isType (name, TOKEN_PERIOD))
		{
			readToken (name);
			if (isType (name, TOKEN_OPEN_SQUARE))
			{
				readToken (name);

				readToken (token);
			}
		}
		readToken (token);
		if (isType (token, TOKEN_PERIOD))
		{

			readToken (name);
			if (isType (name, TOKEN_OPEN_SQUARE))
			{
				readToken (name);

				readToken (token);
			}
			readToken (token);
		}
	}
	if (isType (token, TOKEN_OPEN_PAREN))
	{
		if (isType (name, TOKEN_IDENTIFIER) ||
				isType (name, TOKEN_STRING))
		{
			makeSqlTag (name, SQLTAG_TABLE);
			vStringCopy(token->scope, name->string);
			parseRecord (token);
			vStringClear (token->scope);
		}
	}
	else if (isKeyword (token, KEYWORD_at))
	{
		if (isType (name, TOKEN_IDENTIFIER))
		{
			makeSqlTag (name, SQLTAG_TABLE);
		}
	}
	findCmdTerm (token, FALSE);
	deleteToken (name);
}
