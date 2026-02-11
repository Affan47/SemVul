subquery_is_pushdown_safe(Query *subquery, Query *topquery,
						  pushdown_safety_info *safetyInfo)
{
	SetOperationStmt *topop;


	if (subquery->limitOffset != NULL || subquery->limitCount != NULL)
		return false;


	if (subquery->distinctClause || subquery->hasWindowFuncs)
		safetyInfo->unsafeVolatile = true;


	if (subquery->setOperations == NULL)
		check_output_expressions(subquery, safetyInfo);


	if (subquery == topquery)
	{

		if (subquery->setOperations != NULL)
			if (!recurse_pushdown_safe(subquery->setOperations, topquery,
									   safetyInfo))
				return false;
	}
	else
	{

		if (subquery->setOperations != NULL)
			return false;

		topop = (SetOperationStmt *) topquery->setOperations;
		Assert(topop && IsA(topop, SetOperationStmt));
		compare_tlist_datatypes(subquery->targetList,
								topop->colTypes,
								safetyInfo);
	}
	return true;
}
