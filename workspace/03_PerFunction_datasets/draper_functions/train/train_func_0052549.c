analyzeCTETargetList(ParseState *pstate, CommonTableExpr *cte, List *tlist)
{
	int			numaliases;
	int			varattno;
	ListCell   *tlistitem;


	Assert(cte->ctecolnames == NIL);


	cte->ctecolnames = copyObject(cte->aliascolnames);
	cte->ctecoltypes = cte->ctecoltypmods = cte->ctecolcollations = NIL;
	numaliases = list_length(cte->aliascolnames);
	varattno = 0;
	foreach(tlistitem, tlist)
	{
		TargetEntry *te = (TargetEntry *) lfirst(tlistitem);
		Oid			coltype;
		int32		coltypmod;
		Oid			colcoll;

		if (te->resjunk)
			continue;
		varattno++;
		Assert(varattno == te->resno);
		if (varattno > numaliases)
		{
			char	   *attrname;

			attrname = pstrdup(te->resname);
			cte->ctecolnames = lappend(cte->ctecolnames, makeString(attrname));
		}
		coltype = exprType((Node *) te->expr);
		coltypmod = exprTypmod((Node *) te->expr);
		colcoll = exprCollation((Node *) te->expr);


		if (cte->cterecursive && coltype == UNKNOWNOID)
		{
			coltype = TEXTOID;
			coltypmod = -1;
			if (!OidIsValid(colcoll))
				colcoll = DEFAULT_COLLATION_OID;
		}
		cte->ctecoltypes = lappend_oid(cte->ctecoltypes, coltype);
		cte->ctecoltypmods = lappend_int(cte->ctecoltypmods, coltypmod);
		cte->ctecolcollations = lappend_oid(cte->ctecolcollations, colcoll);
	}
	if (varattno < numaliases)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_COLUMN_REFERENCE),
				 errmsg("WITH query \"%s\" has %d columns available but %d columns specified",
						cte->ctename, varattno, numaliases),
				 parser_errposition(pstate, cte->location)));
}
