PrepareQuery(PrepareStmt *stmt, const char *queryString)
{
	Oid		   *argtypes = NULL;
	int			nargs;
	Query	   *query;
	List	   *query_list,
			   *plan_list;
	int			i;


	if (!stmt->name || stmt->name[0] == '\0')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PSTATEMENT_DEFINITION),
				 errmsg("invalid statement name: must not be empty")));


	nargs = list_length(stmt->argtypes);

	if (nargs)
	{
		ParseState *pstate;
		ListCell   *l;


		pstate = make_parsestate(NULL);
		pstate->p_sourcetext = queryString;

		argtypes = (Oid *) palloc(nargs * sizeof(Oid));
		i = 0;

		foreach(l, stmt->argtypes)
		{
			TypeName   *tn = lfirst(l);
			Oid			toid = typenameTypeId(pstate, tn);

			argtypes[i++] = toid;
		}
	}


	query = parse_analyze_varparams((Node *) copyObject(stmt->query),
									queryString,
									&argtypes, &nargs);


	for (i = 0; i < nargs; i++)
	{
		Oid			argtype = argtypes[i];

		if (argtype == InvalidOid || argtype == UNKNOWNOID)
			ereport(ERROR,
					(errcode(ERRCODE_INDETERMINATE_DATATYPE),
					 errmsg("could not determine data type of parameter $%d",
							i + 1)));
	}


	switch (query->commandType)
	{
		case CMD_SELECT:
		case CMD_INSERT:
		case CMD_UPDATE:
		case CMD_DELETE:

			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PSTATEMENT_DEFINITION),
					 errmsg("utility statements cannot be prepared")));
			break;
	}


	query_list = QueryRewrite(query);


	plan_list = pg_plan_queries(query_list, 0, NULL);


	StorePreparedStatement(stmt->name,
						   stmt->query,
						   queryString,
						   CreateCommandTag((Node *) query),
						   argtypes,
						   nargs,
						   0,
						   plan_list,
						   true);
}
