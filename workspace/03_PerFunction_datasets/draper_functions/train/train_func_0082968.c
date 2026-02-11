find_param_referent(Param *param, deparse_context *context,
					deparse_namespace **dpns_p, ListCell **ancestor_cell_p)
{

	*dpns_p = NULL;
	*ancestor_cell_p = NULL;


	if (param->paramkind == PARAM_EXEC)
	{
		deparse_namespace *dpns;
		PlanState  *child_ps;
		bool		in_same_plan_level;
		ListCell   *lc;

		dpns = (deparse_namespace *) linitial(context->namespaces);
		child_ps = dpns->planstate;
		in_same_plan_level = true;

		foreach(lc, dpns->ancestors)
		{
			PlanState  *ps = (PlanState *) lfirst(lc);
			ListCell   *lc2;


			if (IsA(ps, NestLoopState) &&
				child_ps == innerPlanState(ps) &&
				in_same_plan_level)
			{
				NestLoop   *nl = (NestLoop *) ps->plan;

				foreach(lc2, nl->nestParams)
				{
					NestLoopParam *nlp = (NestLoopParam *) lfirst(lc2);

					if (nlp->paramno == param->paramid)
					{

						*dpns_p = dpns;
						*ancestor_cell_p = lc;
						return (Node *) nlp->paramval;
					}
				}
			}


			foreach(lc2, ps->subPlan)
			{
				SubPlanState *sstate = (SubPlanState *) lfirst(lc2);
				SubPlan    *subplan = (SubPlan *) sstate->xprstate.expr;
				ListCell   *lc3;
				ListCell   *lc4;

				if (child_ps != sstate->planstate)
					continue;


				forboth(lc3, subplan->parParam, lc4, subplan->args)
				{
					int			paramid = lfirst_int(lc3);
					Node	   *arg = (Node *) lfirst(lc4);

					if (paramid == param->paramid)
					{

						*dpns_p = dpns;
						*ancestor_cell_p = lc;
						return arg;
					}
				}


				in_same_plan_level = false;
				break;
			}


			foreach(lc2, ps->initPlan)
			{
				SubPlanState *sstate = (SubPlanState *) lfirst(lc2);

				if (child_ps != sstate->planstate)
					continue;


				Assert(((SubPlan *) sstate->xprstate.expr)->parParam == NIL);


				in_same_plan_level = false;
				break;
			}


			child_ps = ps;
		}
	}


	return NULL;
}
