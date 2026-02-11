addRangeTableEntryForFunction(ParseState *pstate,
							  char *funcname,
							  Node *funcexpr,
							  RangeFunction *rangefunc,
							  bool inFromCl)
{
	RangeTblEntry *rte = makeNode(RangeTblEntry);
	TypeFuncClass functypclass;
	Oid			funcrettype;
	TupleDesc	tupdesc;
	Alias	   *alias = rangefunc->alias;
	List	   *coldeflist = rangefunc->coldeflist;
	Alias	   *eref;

	rte->rtekind = RTE_FUNCTION;
	rte->relid = InvalidOid;
	rte->subquery = NULL;
	rte->funcexpr = funcexpr;
	rte->funccoltypes = NIL;
	rte->funccoltypmods = NIL;
	rte->alias = alias;

	eref = makeAlias(alias ? alias->aliasname : funcname, NIL);
	rte->eref = eref;


	functypclass = get_expr_result_type(funcexpr,
										&funcrettype,
										&tupdesc);


	if (coldeflist != NIL)
	{
		if (functypclass != TYPEFUNC_RECORD)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("a column definition list is only allowed for functions returning \"record\""),
					 parser_errposition(pstate, exprLocation(funcexpr))));
	}
	else
	{
		if (functypclass == TYPEFUNC_RECORD)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("a column definition list is required for functions returning \"record\""),
					 parser_errposition(pstate, exprLocation(funcexpr))));
	}

	if (functypclass == TYPEFUNC_COMPOSITE)
	{

		Assert(tupdesc);

		buildRelationAliases(tupdesc, alias, eref);
	}
	else if (functypclass == TYPEFUNC_SCALAR)
	{

		buildScalarFunctionAlias(funcexpr, funcname, alias, eref);
	}
	else if (functypclass == TYPEFUNC_RECORD)
	{
		ListCell   *col;


		foreach(col, coldeflist)
		{
			ColumnDef  *n = (ColumnDef *) lfirst(col);
			char	   *attrname;
			Oid			attrtype;
			int32		attrtypmod;

			attrname = pstrdup(n->colname);
			if (n->typeName->setof)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
						 errmsg("column \"%s\" cannot be declared SETOF",
								attrname),
						 parser_errposition(pstate, n->typeName->location)));
			typenameTypeIdAndMod(pstate, n->typeName, &attrtype, &attrtypmod);
			eref->colnames = lappend(eref->colnames, makeString(attrname));
			rte->funccoltypes = lappend_oid(rte->funccoltypes, attrtype);
			rte->funccoltypmods = lappend_int(rte->funccoltypmods, attrtypmod);
		}
	}
	else
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
			 errmsg("function \"%s\" in FROM has unsupported return type %s",
					funcname, format_type_be(funcrettype)),
				 parser_errposition(pstate, exprLocation(funcexpr))));


	rte->inh = false;
	rte->inFromCl = inFromCl;

	rte->requiredPerms = 0;
	rte->checkAsUser = InvalidOid;
	rte->selectedCols = NULL;
	rte->modifiedCols = NULL;


	if (pstate != NULL)
		pstate->p_rtable = lappend(pstate->p_rtable, rte);

	return rte;
}
