parseConvert (tokenInfo *const token)
{
	Assert (isKeyword (token, KEYWORD_convert));
	do
	{
		readToken (token);
		if (! isType (token, TOKEN_IDENTIFIER))
			break;
		else if (isType (token, TOKEN_OPEN_PAREN))
		{
			while (! isType (token, TOKEN_CLOSE_PAREN))
				readToken (token);
		}
		else if (isType (token, TOKEN_COLON))
		{
			readToken (token);
			if (! isType (token, TOKEN_OPEN_BRACE))
				break;
			else while (! isType (token, TOKEN_CLOSE_BRACE))
				readToken (token);
		}
	} while (isType (token, TOKEN_COMMA));
}
