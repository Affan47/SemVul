reinitStatement (statementInfo *const st, const boolean partial)
{
	unsigned int i;

	if (! partial)
	{
		st->scope = SCOPE_GLOBAL;
		if (isContextualStatement (st->parent))
			st->declaration = DECL_BASE;
		else
			st->declaration = DECL_NONE;
	}
	st->gotParenName		= FALSE;
	st->implementation		= IMP_DEFAULT;
	st->gotArgs				= FALSE;
	st->gotName				= FALSE;
	st->haveQualifyingName	= FALSE;
	st->argEndPosition		= 0;

	st->tokenIndex			= 0;
	for (i = 0  ;  i < (unsigned int) NumTokens  ;  ++i)
	{
		initToken (st->token [i]);
	}

	initToken (st->context);
	initToken (st->blockName);
	vStringClear (st->parentClasses);


	if (! partial)
		st->member.access = st->member.accessDefault;


	if (!partial)
		initToken(st->firstToken);
}
