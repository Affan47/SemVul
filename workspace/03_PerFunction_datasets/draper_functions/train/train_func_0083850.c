ExecContextForcesOids(PlanState *planstate, bool *hasoids)
{
	if (planstate->state->es_select_into)
	{
		*hasoids = planstate->state->es_into_oids;
		return true;
	}
	else
	{
		ResultRelInfo *ri = planstate->state->es_result_relation_info;

		if (ri != NULL)
		{
			Relation	rel = ri->ri_RelationDesc;

			if (rel != NULL)
			{
				*hasoids = rel->rd_rel->relhasoids;
				return true;
			}
		}
	}

	return false;
}
