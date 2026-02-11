parseMethods (tokenInfo *const token, tokenInfo *const class)
{
	tokenInfo *const name = newToken ();


	do
	{
		readToken (token);
		if (isType (token, TOKEN_STRING) || isKeyword(token, KEYWORD_NONE))
		{
			copyToken (name, token);

			readToken (token);
			if ( isType (token, TOKEN_COLON) )
			{
				readToken (token);
				if ( isKeyword (token, KEYWORD_function) )
				{
					readToken (token);
					if ( isType (token, TOKEN_OPEN_PAREN) )
					{
						skipArgumentList(token);
					}

					if (isType (token, TOKEN_OPEN_CURLY))
					{
						addToScope (name, class->string);
						makeFlexTag (name, FLEXTAG_METHOD);
						parseBlock (token, name);


						readToken (token);
					}
				}
				else
				{
						addToScope (name, class->string);
						makeFlexTag (name, FLEXTAG_PROPERTY);


						readToken (token);
				}
			}
		}
	} while ( isType(token, TOKEN_COMMA) );

	findCmdTerm (token);

	deleteToken (name);
}
