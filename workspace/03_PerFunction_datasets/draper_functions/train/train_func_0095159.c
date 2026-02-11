defGetQualifiedName(DefElem *def)
{
	if (def->arg == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("%s requires a parameter",
						def->defname)));
	switch (nodeTag(def->arg))
	{
		case T_TypeName:
			return ((TypeName *) def->arg)->names;
		case T_List:
			return (List *) def->arg;
		case T_String:

			return list_make1(def->arg);
		default:
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("argument of %s must be a name",
							def->defname)));
	}
	return NIL;
}
