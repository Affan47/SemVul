parseModule (tokenInfo * const token)
{
	tokenInfo *const name = newToken ();
	const vhdlKind kind = isKeyword (token, KEYWORD_ENTITY) ?
		VHDLTAG_ENTITY : VHDLTAG_COMPONENT;
	Assert (isKeyword (token, KEYWORD_ENTITY) ||
		isKeyword (token, KEYWORD_COMPONENT));
	readToken (name);
	if (kind == VHDLTAG_COMPONENT)
	{
		makeVhdlTag (name, VHDLTAG_COMPONENT);
		skipToKeyword (KEYWORD_END);
		fileSkipToCharacter (';');
	}
	else
	{
		readToken (token);
		if (isKeyword (token, KEYWORD_IS))
		{
			makeVhdlTag (name, VHDLTAG_ENTITY);
			skipToKeyword (KEYWORD_END);
			fileSkipToCharacter (';');
		}
	}
	deleteToken (name);
}
