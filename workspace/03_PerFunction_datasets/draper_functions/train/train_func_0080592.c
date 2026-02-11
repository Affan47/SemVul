plpgsql_parse_dblwordrowtype(char *word)
{
	Oid			classOid;
	char	   *cp[3];
	int			i;
	RangeVar   *relvar;
	MemoryContext oldCxt;


	oldCxt = MemoryContextSwitchTo(compile_tmp_cxt);


	i = strlen(word) - 8;
	Assert(word[i] == '%');
	word[i] = '.';
	plpgsql_convert_ident(word, cp, 3);
	word[i] = '%';


	relvar = makeRangeVar(cp[0], cp[1], -1);
	classOid = RangeVarGetRelid(relvar, true);
	if (!OidIsValid(classOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_TABLE),
				 errmsg("relation \"%s.%s\" does not exist", cp[0], cp[1])));


	plpgsql_yylval.dtype = plpgsql_build_datatype(get_rel_type_id(classOid),
												  -1);

	MemoryContextSwitchTo(oldCxt);
	return T_DTYPE;
}
