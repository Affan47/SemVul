set_subqueryscan_references(PlannerGlobal *glob,
							SubqueryScan *plan,
							int rtoffset)
{
	Plan	   *result;


	plan->subplan = set_plan_references(glob, plan->subplan,
										plan->subrtable, plan->subrowmark);


	plan->subrtable = NIL;
	plan->subrowmark = NIL;

	if (trivial_subqueryscan(plan))
	{


		ListCell   *lp,
				   *lc;

		result = plan->subplan;


		result->initPlan = list_concat(plan->scan.plan.initPlan,
									   result->initPlan);


		forboth(lp, plan->scan.plan.targetlist, lc, result->targetlist)
		{
			TargetEntry *ptle = (TargetEntry *) lfirst(lp);
			TargetEntry *ctle = (TargetEntry *) lfirst(lc);

			ctle->resname = ptle->resname;
			ctle->resorigtbl = ptle->resorigtbl;
			ctle->resorigcol = ptle->resorigcol;
		}
	}
	else
	{


		plan->scan.scanrelid += rtoffset;
		plan->scan.plan.targetlist =
			fix_scan_list(glob, plan->scan.plan.targetlist, rtoffset);
		plan->scan.plan.qual =
			fix_scan_list(glob, plan->scan.plan.qual, rtoffset);

		result = (Plan *) plan;
	}

	return result;
}
