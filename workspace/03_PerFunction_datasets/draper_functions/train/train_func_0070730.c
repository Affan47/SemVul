typenameTypeId(ParseState *pstate, const TypeName *typename)
{
	Oid			typoid;

	typoid = LookupTypeName(pstate, typename);
	if (!OidIsValid(typoid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type \"%s\" does not exist",
						TypeNameToString(typename)),
				 parser_errposition(pstate, typename->location)));

	if (!get_typisdefined(typoid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type \"%s\" is only a shell",
						TypeNameToString(typename)),
				 parser_errposition(pstate, typename->location)));
	return typoid;
}
