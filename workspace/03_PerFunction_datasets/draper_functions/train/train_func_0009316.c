RevalidateCachedPlan(CachedPlanSource *plansource, bool useResOwner)
{
	CachedPlan *plan;


	Assert(list_member_ptr(cached_plans_list, plansource));


	plan = plansource->plan;
	if (plan && !plan->dead)
	{


		Assert(plan->refcount > 0);

		if (plan->fully_planned)
			AcquireExecutorLocks(plan->stmt_list, true);
		else
			AcquirePlannerLocks(plan->stmt_list, true);


		if (!plan->dead &&
			TransactionIdIsValid(plan->saved_xmin) &&
			!TransactionIdEquals(plan->saved_xmin, TransactionXmin))
			plan->dead = true;


		if (plan->dead)
		{

			if (plan->fully_planned)
				AcquireExecutorLocks(plan->stmt_list, false);
			else
				AcquirePlannerLocks(plan->stmt_list, false);
		}
	}


	if (plan && plan->dead)
	{
		plansource->plan = NULL;
		ReleaseCachedPlan(plan, false);
		plan = NULL;
	}


	if (!plan)
	{
		bool		snapshot_set = false;
		Node	   *rawtree;
		List	   *slist;
		TupleDesc	resultDesc;


		PushOverrideSearchPath(plansource->search_path);


		if (!ActiveSnapshotSet())
		{
			PushActiveSnapshot(GetTransactionSnapshot());
			snapshot_set = true;
		}


		rawtree = copyObject(plansource->raw_parse_tree);
		if (plansource->parserSetup != NULL)
			slist = pg_analyze_and_rewrite_params(rawtree,
												  plansource->query_string,
												  plansource->parserSetup,
												  plansource->parserSetupArg);
		else
			slist = pg_analyze_and_rewrite(rawtree,
										   plansource->query_string,
										   plansource->param_types,
										   plansource->num_params);

		if (plansource->fully_planned)
		{


			bool		pushed;

			pushed = SPI_push_conditional();

			slist = pg_plan_queries(slist, plansource->cursor_options, NULL);

			SPI_pop_conditional(pushed);
		}


		resultDesc = PlanCacheComputeResultDesc(slist);
		if (resultDesc == NULL && plansource->resultDesc == NULL)
		{

		}
		else if (resultDesc == NULL || plansource->resultDesc == NULL ||
				 !equalTupleDescs(resultDesc, plansource->resultDesc))
		{
			MemoryContext oldcxt;


			if (plansource->fixed_result)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("cached plan must not change result type")));
			oldcxt = MemoryContextSwitchTo(plansource->context);
			if (resultDesc)
				resultDesc = CreateTupleDescCopy(resultDesc);
			if (plansource->resultDesc)
				FreeTupleDesc(plansource->resultDesc);
			plansource->resultDesc = resultDesc;
			MemoryContextSwitchTo(oldcxt);
		}


		if (snapshot_set)
			PopActiveSnapshot();


		PopOverrideSearchPath();


		StoreCachedPlan(plansource, slist, NULL);

		plan = plansource->plan;
	}


	if (useResOwner)
		ResourceOwnerEnlargePlanCacheRefs(CurrentResourceOwner);
	plan->refcount++;
	if (useResOwner)
		ResourceOwnerRememberPlanCacheRef(CurrentResourceOwner, plan);

	return plan;
}
