skipType (tokenInfo *const token)
{
again:

	if (isType (token, TOKEN_OPEN_PAREN))
	{
		skipToMatched (token);
		return;
	}


	if (isType (token, TOKEN_IDENTIFIER))
	{
		readToken (token);
		if (isType (token, TOKEN_DOT))
		{
			readToken (token);
			Assert (isType (token, TOKEN_IDENTIFIER));
			readToken (token);
		}
		return;
	}


	if (isKeyword (token, KEYWORD_struct) || isKeyword (token, KEYWORD_interface))
	{
		readToken (token);
		Assert (isType (token, TOKEN_OPEN_CURLY));
		skipToMatched (token);
		return;
	}


	if (isType (token, TOKEN_OPEN_SQUARE))
	{
		skipToMatched (token);
		goto again;
	}


	if (isType (token, TOKEN_STAR) || isKeyword (token, KEYWORD_chan) || isType (token, TOKEN_LEFT_ARROW))
	{
		readToken (token);
		goto again;
	}


	if (isKeyword (token, KEYWORD_map))
	{
		readToken (token);
		Assert (isType (token, TOKEN_OPEN_SQUARE));
		skipToMatched (token);
		goto again;
	}


	if (isKeyword (token, KEYWORD_func))
	{
		readToken (token);
		Assert (isType (token, TOKEN_OPEN_PAREN));

		skipToMatched (token);


		goto again;
	}
}
