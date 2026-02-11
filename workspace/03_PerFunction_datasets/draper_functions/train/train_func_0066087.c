extract_grouping_ops(List *groupClause)
{
	int			numCols = list_length(groupClause);
	int			colno = 0;
	Oid		   *groupOperators;
	ListCell   *glitem;

	groupOperators = (Oid *) palloc(sizeof(Oid) * numCols);

	foreach(glitem, groupClause)
	{
		SortGroupClause *groupcl = (SortGroupClause *) lfirst(glitem);

		groupOperators[colno] = groupcl->eqop;
		Assert(OidIsValid(groupOperators[colno]));
		colno++;
	}

	return groupOperators;
}
