set_upper_references(PlannerGlobal *glob, Plan *plan, int rtoffset)
{
	Plan	   *subplan = plan->lefttree;
	indexed_tlist *subplan_itlist;
	List	   *output_targetlist;
	ListCell   *l;

	subplan_itlist = build_tlist_index(subplan->targetlist);

	output_targetlist = NIL;
	foreach(l, plan->targetlist)
	{
		TargetEntry *tle = (TargetEntry *) lfirst(l);
		Node	   *newexpr;

		newexpr = fix_upper_expr(glob,
								 (Node *) tle->expr,
								 subplan_itlist,
								 rtoffset);
		tle = flatCopyTargetEntry(tle);
		tle->expr = (Expr *) newexpr;
		output_targetlist = lappend(output_targetlist, tle);
	}
	plan->targetlist = output_targetlist;

	plan->qual = (List *)
		fix_upper_expr(glob,
					   (Node *) plan->qual,
					   subplan_itlist,
					   rtoffset);

	pfree(subplan_itlist);
}
