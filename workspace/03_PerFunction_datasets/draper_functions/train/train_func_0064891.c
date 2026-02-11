parseComment (tokenInfo *const token)
{


	while (! isKeyword (token, KEYWORD_is))
	{
		readToken (token);
	}
	readToken (token);
	if ( isType(token, TOKEN_OPEN_CURLY) )
	{
		findToken (token, TOKEN_CLOSE_CURLY);
	}

	findCmdTerm (token, TRUE);
}
