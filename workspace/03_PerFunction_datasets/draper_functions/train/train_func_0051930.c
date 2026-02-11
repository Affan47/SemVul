transformIndexConstraints(CreateStmtContext *cxt)
{
	IndexStmt  *index;
	List	   *indexlist = NIL;
	ListCell   *lc;


	foreach(lc, cxt->ixconstraints)
	{
		Constraint *constraint = (Constraint *) lfirst(lc);

		Assert(IsA(constraint, Constraint));
		Assert(constraint->contype == CONSTR_PRIMARY ||
			   constraint->contype == CONSTR_UNIQUE ||
			   constraint->contype == CONSTR_EXCLUSION);

		index = transformIndexConstraint(constraint, cxt);

		indexlist = lappend(indexlist, index);
	}


	foreach(lc, cxt->inh_indexes)
	{
		index = (IndexStmt *) lfirst(lc);

		if (index->primary)
		{
			if (cxt->pkey != NULL)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
						 errmsg("multiple primary keys for table \"%s\" are not allowed",
								cxt->relation->relname)));
			cxt->pkey = index;
		}

		indexlist = lappend(indexlist, index);
	}


	Assert(cxt->alist == NIL);
	if (cxt->pkey != NULL)
	{

		cxt->alist = list_make1(cxt->pkey);
	}

	foreach(lc, indexlist)
	{
		bool		keep = true;
		ListCell   *k;

		index = lfirst(lc);


		if (index == cxt->pkey)
			continue;

		foreach(k, cxt->alist)
		{
			IndexStmt  *priorindex = lfirst(k);

			if (equal(index->indexParams, priorindex->indexParams) &&
				equal(index->whereClause, priorindex->whereClause) &&
				equal(index->excludeOpNames, priorindex->excludeOpNames) &&
				strcmp(index->accessMethod, priorindex->accessMethod) == 0 &&
				index->deferrable == priorindex->deferrable &&
				index->initdeferred == priorindex->initdeferred)
			{
				priorindex->unique |= index->unique;


				if (priorindex->idxname == NULL)
					priorindex->idxname = index->idxname;
				keep = false;
				break;
			}
		}

		if (keep)
			cxt->alist = lappend(cxt->alist, index);
	}
}
