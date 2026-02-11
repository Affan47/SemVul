show_agg_keys(AggState *astate, List *ancestors,
			  ExplainState *es)
{
	Agg		   *plan = (Agg *) astate->ss.ps.plan;

	if (plan->numCols > 0 || plan->groupingSets)
	{

		ancestors = lcons(astate, ancestors);

		if (plan->groupingSets)
			show_grouping_sets(outerPlanState(astate), plan, ancestors, es);
		else
			show_sort_group_keys(outerPlanState(astate), "Group Key",
								 plan->numCols, plan->grpColIdx,
								 NULL, NULL, NULL,
								 ancestors, es);

		ancestors = list_delete_first(ancestors);
	}
}
