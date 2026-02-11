parseMethods (tokenInfo *const token, tokenInfo *const class)
{
	tokenInfo *const name = newToken ();
	boolean has_methods = FALSE;


	do
	{
		readToken (token);
		if (isType (token, TOKEN_CLOSE_CURLY))
		{


			has_methods = FALSE;
			goto cleanUp;
		}

		if (isType (token, TOKEN_STRING) || isKeyword(token, KEYWORD_NONE))
		{
			copyToken(name, token);

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
						has_methods = TRUE;
						addToScope (name, class->string);
						makeJsTag (name, JSTAG_METHOD);
						parseBlock (token, name);


						readToken (token);
					}
				}
				else
				{
						has_methods = TRUE;
						addToScope (name, class->string);
						makeJsTag (name, JSTAG_PROPERTY);


						readToken (token);
				}
			}
		}
	} while ( isType(token, TOKEN_COMMA) );

	findCmdTerm (token);

cleanUp:
	deleteToken (name);

	return has_methods;
}
