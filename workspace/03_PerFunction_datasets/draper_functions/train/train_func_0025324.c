PlanCacheFuncCallback(Datum arg, int cacheid, ItemPointer tuplePtr)
{
	ListCell   *lc1;

	foreach(lc1, cached_plans_list)
	{
		CachedPlanSource *plansource = (CachedPlanSource *) lfirst(lc1);
		CachedPlan *plan = plansource->plan;


		if (!plan || plan->dead)
			continue;
		if (plan->fully_planned)
		{

			ListCell   *lc2;

			foreach(lc2, plan->stmt_list)
			{
				PlannedStmt *plannedstmt = (PlannedStmt *) lfirst(lc2);
				ListCell   *lc3;

				Assert(!IsA(plannedstmt, Query));
				if (!IsA(plannedstmt, PlannedStmt))
					continue;
				foreach(lc3, plannedstmt->invalItems)
				{
					PlanInvalItem *item = (PlanInvalItem *) lfirst(lc3);

					if (item->cacheId != cacheid)
						continue;
					if (tuplePtr == NULL ||
						ItemPointerEquals(tuplePtr, &item->tupleId))
					{

						plan->dead = true;
						break;
					}
				}
				if (plan->dead)
					break;
			}
		}
		else
		{

			ListCell   *lc2;

			foreach(lc2, plan->invalItems)
			{
				PlanInvalItem *item = (PlanInvalItem *) lfirst(lc2);

				if (item->cacheId != cacheid)
					continue;
				if (tuplePtr == NULL ||
					ItemPointerEquals(tuplePtr, &item->tupleId))
				{

					plan->dead = true;
					break;
				}
			}
		}
	}
}
