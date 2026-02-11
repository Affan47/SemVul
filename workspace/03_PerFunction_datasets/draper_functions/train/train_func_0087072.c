plpgsql_parse_cwordrowtype(List *idents)
{
	Oid			classOid;
	RangeVar   *relvar;
	MemoryContext oldCxt;

	if (list_length(idents) != 2)
		return NULL;


	oldCxt = MemoryContextSwitchTo(compile_tmp_cxt);


	relvar = makeRangeVar(strVal(linitial(idents)),
						  strVal(lsecond(idents)),
						  -1);
	classOid = RangeVarGetRelid(relvar, true);
	if (!OidIsValid(classOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_TABLE),
				 errmsg("relation \"%s.%s\" does not exist",
						strVal(linitial(idents)), strVal(lsecond(idents)))));

	MemoryContextSwitchTo(oldCxt);


	return plpgsql_build_datatype(get_rel_type_id(classOid), -1);
}
