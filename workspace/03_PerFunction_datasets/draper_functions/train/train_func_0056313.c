parseActionScript (tokenInfo *const token)
{
	do
	{
		readToken (token);

		if (isType (token, TOKEN_LESS_THAN))
		{


			readToken (token);
			if (isType (token, TOKEN_EQUAL_SIGN))
			{
				if (isType (token, TOKEN_OPEN_SQUARE))
				{
					readToken (token);
					if (isKeyword (token, KEYWORD_cdata))
					{
						readToken (token);
					}
				}
			}
		}
		if (isType (token, TOKEN_CLOSE_SQUARE))
		{


			readToken (token);
			if (isType (token, TOKEN_CLOSE_SQUARE))
			{
				readToken (token);
				if (isType (token, TOKEN_GREATER_THAN))
				{
					return TRUE;
				}
			}
		}
		else if (isType (token, TOKEN_CLOSE_MXML))
		{


			readToken (token);
			readToken (token);
			return TRUE;
		}
		else if (isType (token, TOKEN_OPEN_MXML))
		{
			parseMXML (token);
		}
		else
		{
			if (isType(token, TOKEN_KEYWORD))
			{
				switch (token->keyword)
				{
					case KEYWORD_function:	parseFunction (token); break;
					default:				parseLine (token); break;
				}
			}
			else
			{
				parseLine (token);
			}
		}
	} while (TRUE);
}
