get_restriction_qual_cost(PlannerInfo *root, RelOptInfo *baserel,
						  ParamPathInfo *param_info,
						  QualCost *qpqual_cost)
{
	if (param_info)
	{

		cost_qual_eval(qpqual_cost, param_info->ppi_clauses, root);

		qpqual_cost->startup += baserel->baserestrictcost.startup;
		qpqual_cost->per_tuple += baserel->baserestrictcost.per_tuple;
	}
	else
		*qpqual_cost = baserel->baserestrictcost;
}
