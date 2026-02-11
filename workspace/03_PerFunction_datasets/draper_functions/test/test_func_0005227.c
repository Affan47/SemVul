_SPI_save_plan(SPIPlanPtr plan)
{
	SPIPlanPtr	newplan;
	MemoryContext plancxt;
	MemoryContext oldcxt;
	ListCell   *lc;

	Assert(!plan->saved);


	plancxt = AllocSetContextCreate(CacheMemoryContext,
									"SPI Plan",
									ALLOCSET_SMALL_MINSIZE,
									ALLOCSET_SMALL_INITSIZE,
									ALLOCSET_SMALL_MAXSIZE);
	oldcxt = MemoryContextSwitchTo(plancxt);


	newplan = (SPIPlanPtr) palloc(sizeof(_SPI_plan));
	newplan->magic = _SPI_PLAN_MAGIC;
	newplan->saved = true;
	newplan->plancache_list = NIL;
	newplan->plancxt = plancxt;
	newplan->cursor_options = plan->cursor_options;
	newplan->nargs = plan->nargs;
	if (plan->nargs > 0)
	{
		newplan->argtypes = (Oid *) palloc(plan->nargs * sizeof(Oid));
		memcpy(newplan->argtypes, plan->argtypes, plan->nargs * sizeof(Oid));
	}
	else
		newplan->argtypes = NULL;

	foreach(lc, plan->plancache_list)
	{
		CachedPlanSource *plansource = (CachedPlanSource *) lfirst(lc);
		CachedPlanSource *newsource;
		CachedPlan *cplan;


		cplan = plansource->plan;

		newsource = CreateCachedPlan(plansource->raw_parse_tree,
									 plansource->query_string,
									 plansource->commandTag,
									 newplan->argtypes,
									 newplan->nargs,
									 newplan->cursor_options,
									 cplan->stmt_list,
									 true,
									 false);

		newplan->plancache_list = lappend(newplan->plancache_list, newsource);
	}

	MemoryContextSwitchTo(oldcxt);

	return newplan;
}
