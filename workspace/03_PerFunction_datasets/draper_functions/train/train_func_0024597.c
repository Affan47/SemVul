have_relevant_joinclause(PlannerInfo *root,
						 RelOptInfo *rel1, RelOptInfo *rel2)
{
	bool		result = false;
	Relids		join_relids;
	List	   *joininfo;
	ListCell   *l;

	join_relids = bms_union(rel1->relids, rel2->relids);


	if (list_length(rel1->joininfo) <= list_length(rel2->joininfo))
		joininfo = rel1->joininfo;
	else
		joininfo = rel2->joininfo;

	foreach(l, joininfo)
	{
		RestrictInfo *rinfo = (RestrictInfo *) lfirst(l);

		if (bms_is_subset(rinfo->required_relids, join_relids))
		{
			result = true;
			break;
		}
	}

	bms_free(join_relids);

	return result;
}
