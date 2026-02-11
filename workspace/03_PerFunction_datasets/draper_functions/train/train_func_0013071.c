transformDistinctClause(ParseState *pstate, List *distinctlist,
						List **targetlist, List **sortClause)
{
	List	   *result = NIL;
	ListCell   *slitem;
	ListCell   *dlitem;


	if (distinctlist == NIL)
		return NIL;

	if (linitial(distinctlist) == NULL)
	{


		*sortClause = addAllTargetsToSortList(pstate,
											  *sortClause,
											  *targetlist,
											  true);


		foreach(slitem, *sortClause)
		{
			SortClause *scl = (SortClause *) lfirst(slitem);
			TargetEntry *tle = get_sortgroupclause_tle(scl, *targetlist);

			if (tle->resjunk)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_COLUMN_REFERENCE),
						 errmsg("for SELECT DISTINCT, ORDER BY expressions must appear in select list")));
			else
				result = lappend(result, copyObject(scl));
		}
	}
	else
	{


		ListCell   *nextsortlist = list_head(*sortClause);

		foreach(dlitem, distinctlist)
		{
			TargetEntry *tle;

			tle = findTargetlistEntry(pstate, lfirst(dlitem),
									  targetlist, DISTINCT_ON_CLAUSE);

			if (nextsortlist != NULL)
			{
				SortClause *scl = (SortClause *) lfirst(nextsortlist);

				if (tle->ressortgroupref != scl->tleSortGroupRef)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_COLUMN_REFERENCE),
							 errmsg("SELECT DISTINCT ON expressions must match initial ORDER BY expressions")));
				result = lappend(result, copyObject(scl));
				nextsortlist = lnext(nextsortlist);
			}
			else
			{
				*sortClause = addTargetToSortList(pstate, tle,
												  *sortClause, *targetlist,
												  SORTBY_ASC, NIL, true);


				foreach(slitem, *sortClause)
				{
					SortClause *scl = (SortClause *) lfirst(slitem);

					if (tle->ressortgroupref == scl->tleSortGroupRef)
					{
						result = lappend(result, copyObject(scl));
						break;
					}
				}
				if (slitem == NULL)
					elog(ERROR, "failed to add DISTINCT ON clause to target list");
			}
		}
	}

	return result;
}
