make_recursive_union(List *tlist,
					 Plan *lefttree,
					 Plan *righttree,
					 int wtParam,
					 List *distinctList,
					 long numGroups)
{
	RecursiveUnion *node = makeNode(RecursiveUnion);
	Plan	   *plan = &node->plan;
	int			numCols = list_length(distinctList);

	cost_recursive_union(plan, lefttree, righttree);

	plan->targetlist = tlist;
	plan->qual = NIL;
	plan->lefttree = lefttree;
	plan->righttree = righttree;
	node->wtParam = wtParam;


	node->numCols = numCols;
	if (numCols > 0)
	{
		int			keyno = 0;
		AttrNumber *dupColIdx;
		Oid		   *dupOperators;
		ListCell   *slitem;

		dupColIdx = (AttrNumber *) palloc(sizeof(AttrNumber) * numCols);
		dupOperators = (Oid *) palloc(sizeof(Oid) * numCols);

		foreach(slitem, distinctList)
		{
			SortGroupClause *sortcl = (SortGroupClause *) lfirst(slitem);
			TargetEntry *tle = get_sortgroupclause_tle(sortcl,
													   plan->targetlist);

			dupColIdx[keyno] = tle->resno;
			dupOperators[keyno] = sortcl->eqop;
			Assert(OidIsValid(dupOperators[keyno]));
			keyno++;
		}
		node->dupColIdx = dupColIdx;
		node->dupOperators = dupOperators;
	}
	node->numGroups = numGroups;

	return node;
}
