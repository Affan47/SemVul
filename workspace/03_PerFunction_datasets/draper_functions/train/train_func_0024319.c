select_mergejoin_clauses(PlannerInfo *root,
						 RelOptInfo *joinrel,
						 RelOptInfo *outerrel,
						 RelOptInfo *innerrel,
						 List *restrictlist,
						 JoinType jointype)
{
	List	   *result_list = NIL;
	bool		isouterjoin = IS_OUTER_JOIN(jointype);
	bool		have_nonmergeable_joinclause = false;
	ListCell   *l;

	foreach(l, restrictlist)
	{
		RestrictInfo *restrictinfo = (RestrictInfo *) lfirst(l);


		if (isouterjoin && restrictinfo->is_pushed_down)
			continue;


		if (!restrictinfo->can_join ||
			restrictinfo->mergeopfamilies == NIL)
		{


			if (!restrictinfo->clause || !IsA(restrictinfo->clause, Const))
				have_nonmergeable_joinclause = true;
			continue;
		}


		if (bms_is_subset(restrictinfo->left_relids, outerrel->relids) &&
			bms_is_subset(restrictinfo->right_relids, innerrel->relids))
		{

			restrictinfo->outer_is_left = true;
		}
		else if (bms_is_subset(restrictinfo->left_relids, innerrel->relids) &&
				 bms_is_subset(restrictinfo->right_relids, outerrel->relids))
		{

			restrictinfo->outer_is_left = false;
		}
		else
		{
			have_nonmergeable_joinclause = true;
			continue;
		}


		cache_mergeclause_eclasses(root, restrictinfo);

		if (EC_MUST_BE_REDUNDANT(restrictinfo->left_ec) ||
			EC_MUST_BE_REDUNDANT(restrictinfo->right_ec))
		{
			have_nonmergeable_joinclause = true;
			continue;
		}

		result_list = lappend(result_list, restrictinfo);
	}


	if (have_nonmergeable_joinclause)
	{
		switch (jointype)
		{
			case JOIN_RIGHT:
				return NIL;
			case JOIN_FULL:
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("FULL JOIN is only supported with merge-joinable join conditions")));
				break;
			default:

				break;
		}
	}

	return result_list;
}
