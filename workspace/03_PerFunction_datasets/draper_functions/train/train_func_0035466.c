make_pathkeys_for_sortclauses(PlannerInfo *root,
							  List *sortclauses,
							  List *tlist,
							  bool canonicalize)
{
	List	   *pathkeys = NIL;
	ListCell   *l;

	foreach(l, sortclauses)
	{
		SortGroupClause *sortcl = (SortGroupClause *) lfirst(l);
		Expr	   *sortkey;
		PathKey    *pathkey;

		sortkey = (Expr *) get_sortgroupclause_expr(sortcl, tlist);
		Assert(OidIsValid(sortcl->sortop));
		pathkey = make_pathkey_from_sortinfo(root,
											 sortkey,
											 sortcl->sortop,
											 sortcl->nulls_first,
											 sortcl->tleSortGroupRef,
											 canonicalize);


		if (canonicalize)
		{
			if (!pathkey_is_redundant(pathkey, pathkeys))
				pathkeys = lappend(pathkeys, pathkey);
		}
		else
			pathkeys = lappend(pathkeys, pathkey);
	}
	return pathkeys;
}
