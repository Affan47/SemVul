planstate_walk_subplans(List *plans, bool (*walker) (), void *context)
{
	ListCell   *lc;

	foreach(lc, plans)
	{
		SubPlanState *sps = (SubPlanState *) lfirst(lc);

		Assert(IsA(sps, SubPlanState));
		if (walker(sps->planstate, context))
			return true;
	}

	return false;
}
