processName (statementInfo *const st)
{
	Assert (isType (activeToken (st), TOKEN_NAME));
	if (st->gotName  &&  st->declaration == DECL_NONE)
		st->declaration = DECL_BASE;
	st->gotName = TRUE;
	st->haveQualifyingName = TRUE;
}
