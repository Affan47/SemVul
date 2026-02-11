parseIf (tokenInfo *const token)
{
	boolean read_next_token = TRUE;


	readToken (token);

	if (isKeyword (token, KEYWORD_if))
	{


		readToken (token);
	}

	if (isType (token, TOKEN_OPEN_PAREN))
	{


		skipArgumentList(token);
	}

	if (isType (token, TOKEN_OPEN_CURLY))
	{


		parseBlock (token, token);
	}
	else
	{
		findCmdTerm (token);


		read_next_token = isType (token, TOKEN_SEMICOLON);
	}
	return read_next_token;
}
