ExplainMemberNodes(List *plans, PlanState **planstates,
				   List *ancestors, ExplainState *es)
{
	int			nplans = list_length(plans);
	int			j;

	for (j = 0; j < nplans; j++)
		ExplainNode(planstates[j], ancestors,
					"Member", NULL, es);
}
