parseCDATA (tokenInfo *const token)
{
	if (isType (token, TOKEN_LESS_THAN))
	{


		readToken (token);
		if (isType (token, TOKEN_EXCLAMATION))
		{


				readToken (token);
				if (isKeyword (token, KEYWORD_cdata))
				{
					readToken (token);
					if (isType (token, TOKEN_OPEN_SQUARE))
					{
						parseActionScript (token);
						if (isType (token, TOKEN_CLOSE_SQUARE))
						{
							readToken (token);
							if (isType (token, TOKEN_CLOSE_SQUARE))
							{
								readToken (token);
							}
						}
					}
				}

		}
	}
	else
	{
		parseActionScript (token);
	}
	return TRUE;
}
