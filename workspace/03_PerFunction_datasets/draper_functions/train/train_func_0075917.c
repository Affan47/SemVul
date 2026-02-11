set_plan_references(PlannerInfo *root, Plan *plan)
{
	PlannerGlobal *glob = root->glob;
	int			rtoffset = list_length(glob->finalrtable);
	ListCell   *lc;


	add_rtes_to_flat_rtable(root, false);


	foreach(lc, root->rowMarks)
	{
		PlanRowMark *rc = (PlanRowMark *) lfirst(lc);
		PlanRowMark *newrc;

		Assert(IsA(rc, PlanRowMark));


		newrc = (PlanRowMark *) palloc(sizeof(PlanRowMark));
		memcpy(newrc, rc, sizeof(PlanRowMark));


		newrc->rti += rtoffset;
		newrc->prti += rtoffset;

		glob->finalrowmarks = lappend(glob->finalrowmarks, newrc);
	}


	return set_plan_refs(root, plan, rtoffset);
}
