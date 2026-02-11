alias_relid_set(PlannerInfo *root, Relids relids)
{
	Relids		result = NULL;
	Relids		tmprelids;
	int			rtindex;

	tmprelids = bms_copy(relids);
	while ((rtindex = bms_first_member(tmprelids)) >= 0)
	{
		RangeTblEntry *rte = rt_fetch(rtindex, root->parse->rtable);

		if (rte->rtekind == RTE_JOIN)
			result = bms_join(result, get_relids_for_join(root, rtindex));
		else
			result = bms_add_member(result, rtindex);
	}
	bms_free(tmprelids);
	return result;
}
