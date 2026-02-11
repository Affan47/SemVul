has_nullable_targetlist(Query *subquery)
{
	ListCell   *l;

	foreach(l, subquery->targetList)
	{
		TargetEntry *tle = (TargetEntry *) lfirst(l);


		if (tle->resjunk)
			continue;


		if (!contain_vars_of_level((Node *) tle->expr, 0))
			return false;


		if (contain_nonstrict_functions((Node *) tle->expr))
			return false;


	}
	return true;
}
