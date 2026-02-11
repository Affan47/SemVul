transformSortClause(ParseState *pstate,
					List *orderlist,
					List **targetlist,
					bool resolveUnknown)
{
	List	   *sortlist = NIL;
	ListCell   *olitem;

	foreach(olitem, orderlist)
	{
		SortBy	   *sortby = lfirst(olitem);
		TargetEntry *tle;

		tle = findTargetlistEntry(pstate, sortby->node,
								  targetlist, ORDER_CLAUSE);

		sortlist = addTargetToSortList(pstate, tle,
									   sortlist, *targetlist,
									   sortby->sortby_kind,
									   sortby->useOp,
									   resolveUnknown);
	}

	return sortlist;
}
