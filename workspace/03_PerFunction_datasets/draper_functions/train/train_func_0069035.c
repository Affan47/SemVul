get_aggregate_argtypes(Aggref *aggref, Oid *inputTypes)
{
	int			numArguments = 0;
	ListCell   *lc;


	foreach(lc, aggref->aggdirectargs)
	{
		Node	   *expr = (Node *) lfirst(lc);

		inputTypes[numArguments] = exprType(expr);
		numArguments++;
	}


	foreach(lc, aggref->args)
	{
		TargetEntry *tle = (TargetEntry *) lfirst(lc);


		if (tle->resjunk)
			continue;

		inputTypes[numArguments] = exprType((Node *) tle->expr);
		numArguments++;
	}

	return numArguments;
}
