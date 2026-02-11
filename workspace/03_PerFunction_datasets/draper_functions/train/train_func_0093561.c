qualifyFunctionTag (const statementInfo *const st,
								const tokenInfo *const nameToken)
{
	if (isType (nameToken, TOKEN_NAME))
	{
		const tagType type = (isLanguage (Lang_java) || isLanguage (Lang_csharp) || isLanguage (Lang_vala))
								? TAG_METHOD : TAG_FUNCTION;
		const boolean isFileScope =
				(boolean) (st->member.access == ACCESS_PRIVATE ||
						   (!isMember (st)  &&  st->scope == SCOPE_STATIC));

		makeTag (nameToken, st, isFileScope, type);
	}
}
