parseSubProgram (tokenInfo * const token)
{
	tokenInfo *const name = newToken ();
	boolean endSubProgram = FALSE;
	const vhdlKind kind = isKeyword (token, KEYWORD_FUNCTION) ?
		VHDLTAG_FUNCTION : VHDLTAG_PROCEDURE;
	Assert (isKeyword (token, KEYWORD_FUNCTION) ||
		isKeyword (token, KEYWORD_PROCEDURE));
	readToken (name);
	readToken (token);
	if (isType (token, TOKEN_OPEN_PAREN))
	{
		skipToMatched (token);
	}

	if (kind == VHDLTAG_FUNCTION)
	{
		if (isKeyword (token, KEYWORD_RETURN))
		{

			readToken (token);
			while (! isKeyword (token, KEYWORD_IS) &&
					! isType (token, TOKEN_SEMICOLON))
			{
				readToken (token);
			}
		}
	}

	if (isType (token, TOKEN_SEMICOLON))
	{
		makeVhdlTag (name, VHDLTAG_PROTOTYPE);
	}
	else if (isKeyword (token, KEYWORD_IS))
	{
		if (kind == VHDLTAG_FUNCTION)
		{
			makeVhdlTag (name, VHDLTAG_FUNCTION);
			do
			{
				readToken (token);
				if (isKeyword (token, KEYWORD_END))
				{
					readToken (token);
					endSubProgram = isKeywordOrIdent (token,
						KEYWORD_FUNCTION, name->string);
					fileSkipToCharacter (';');
				}
				else
				{
					parseKeywords (token, TRUE);
				}
			} while (!endSubProgram);
		}
		else
		{
			makeVhdlTag (name, VHDLTAG_PROCEDURE);
			do
			{
				readToken (token);
				if (isKeyword (token, KEYWORD_END))
				{
					readToken (token);
					endSubProgram = isKeywordOrIdent (token,
						KEYWORD_PROCEDURE, name->string);
					fileSkipToCharacter (';');
				}
				else
				{
					parseKeywords (token, TRUE);
				}
			} while (!endSubProgram);
		}
	}
	deleteToken (name);
}
