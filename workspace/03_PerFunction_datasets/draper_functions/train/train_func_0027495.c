SS_finalize_plan(PlannerInfo *root, Plan *plan, bool attach_initplans)
{
	Bitmapset  *valid_params,
			   *initExtParam,
			   *initSetParam;
	Cost		initplan_cost;
	int			paramid;
	ListCell   *l;


	initExtParam = initSetParam = NULL;
	initplan_cost = 0;
	foreach(l, root->init_plans)
	{
		SubPlan    *initsubplan = (SubPlan *) lfirst(l);
		Plan	   *initplan = planner_subplan_get_plan(root, initsubplan);
		ListCell   *l2;

		initExtParam = bms_add_members(initExtParam, initplan->extParam);
		foreach(l2, initsubplan->setParam)
		{
			initSetParam = bms_add_member(initSetParam, lfirst_int(l2));
		}
		initplan_cost += initsubplan->startup_cost + initsubplan->per_call_cost;
	}


	valid_params = bms_copy(initSetParam);
	paramid = 0;
	foreach(l, root->glob->paramlist)
	{
		PlannerParamItem *pitem = (PlannerParamItem *) lfirst(l);

		if (pitem->abslevel < root->query_level)
		{

			valid_params = bms_add_member(valid_params, paramid);
		}

		paramid++;
	}


	(void) finalize_plan(root, plan, valid_params, NULL);

	bms_free(valid_params);


	if (attach_initplans)
	{
		plan->initPlan = root->init_plans;
		root->init_plans = NIL;


		plan->allParam = bms_add_members(plan->allParam, initExtParam);
		plan->allParam = bms_add_members(plan->allParam, initSetParam);

		plan->extParam = bms_add_members(plan->extParam, initExtParam);

		plan->extParam = bms_del_members(plan->extParam, initSetParam);

		if (bms_is_empty(plan->extParam))
			plan->extParam = NULL;

		plan->startup_cost += initplan_cost;
		plan->total_cost += initplan_cost;
	}
}
