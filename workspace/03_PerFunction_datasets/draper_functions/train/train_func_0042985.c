use_physical_tlist(PlannerInfo *root, RelOptInfo *rel)
{
	int			i;
	ListCell   *lc;


	if (rel->rtekind != RTE_RELATION &&
		rel->rtekind != RTE_SUBQUERY &&
		rel->rtekind != RTE_FUNCTION &&
		rel->rtekind != RTE_VALUES &&
		rel->rtekind != RTE_CTE)
		return false;


	if (rel->reloptkind != RELOPT_BASEREL)
		return false;


	for (i = rel->min_attr; i <= 0; i++)
	{
		if (!bms_is_empty(rel->attr_needed[i - rel->min_attr]))
			return false;
	}


	foreach(lc, root->placeholder_list)
	{
		PlaceHolderInfo *phinfo = (PlaceHolderInfo *) lfirst(lc);

		if (bms_nonempty_difference(phinfo->ph_needed, rel->relids) &&
			bms_is_subset(phinfo->ph_eval_at, rel->relids))
			return false;
	}

	return true;
}
