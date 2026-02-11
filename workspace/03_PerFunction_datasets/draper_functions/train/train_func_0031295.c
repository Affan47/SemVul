addRangeTableEntryForSubquery(ParseState *pstate,
							  Query *subquery,
							  Alias *alias,
							  bool inFromCl)
{
	RangeTblEntry *rte = makeNode(RangeTblEntry);
	char	   *refname = alias->aliasname;
	Alias	   *eref;
	int			numaliases;
	int			varattno;
	ListCell   *tlistitem;

	rte->rtekind = RTE_SUBQUERY;
	rte->relid = InvalidOid;
	rte->subquery = subquery;
	rte->alias = alias;

	eref = copyObject(alias);
	numaliases = list_length(eref->colnames);


	varattno = 0;
	foreach(tlistitem, subquery->targetList)
	{
		TargetEntry *te = (TargetEntry *) lfirst(tlistitem);

		if (te->resjunk)
			continue;
		varattno++;
		Assert(varattno == te->resno);
		if (varattno > numaliases)
		{
			char	   *attrname;

			attrname = pstrdup(te->resname);
			eref->colnames = lappend(eref->colnames, makeString(attrname));
		}
	}
	if (varattno < numaliases)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_COLUMN_REFERENCE),
				 errmsg("table \"%s\" has %d columns available but %d columns specified",
						refname, varattno, numaliases)));

	rte->eref = eref;


	rte->inh = false;
	rte->inFromCl = inFromCl;

	rte->requiredPerms = 0;
	rte->checkAsUser = InvalidOid;


	if (pstate != NULL)
		pstate->p_rtable = lappend(pstate->p_rtable, rte);

	return rte;
}
