parseStructureStmt (tokenInfo *const token)
{
	tokenInfo *name;
	Assert (isKeyword (token, KEYWORD_structure));
	readToken (token);
	if (isType (token, TOKEN_OPERATOR) &&
		strcmp (vStringValue (token->string), "/") == 0)
	{
		readToken (token);
		if (isType (token, TOKEN_IDENTIFIER))
			makeFortranTag (token, TAG_DERIVED_TYPE);
		name = newTokenFrom (token);
		skipPast (token, TOKEN_OPERATOR);
	}
	else
	{
		name = newToken ();
		name->type = TOKEN_IDENTIFIER;
		name->tag = TAG_DERIVED_TYPE;
		vStringCopyS (name->string, "anonymous");
	}
	while (isType (token, TOKEN_IDENTIFIER))
	{
		makeFortranTag (token, TAG_COMPONENT);
		readToken (token);
		if (isType (token, TOKEN_COMMA))
			readToken (token);
	}
	skipToNextStatement (token);
	ancestorPush (name);
	while (! isKeyword (token, KEYWORD_end))
		parseFieldDefinition (token);
	readSubToken (token);

	skipToNextStatement (token);
	ancestorPop ();
	deleteToken (name);
}
