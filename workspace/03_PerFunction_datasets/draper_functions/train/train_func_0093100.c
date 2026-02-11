set_uppernode_references(Plan *plan, Index subvarno)
{
	Plan	   *subplan = plan->lefttree;
	indexed_tlist *subplan_itlist;
	List	   *output_targetlist;
	ListCell   *l;

	if (subplan != NULL)
		subplan_itlist = build_tlist_index(subplan->targetlist);
	else
		subplan_itlist = build_tlist_index(NIL);

	output_targetlist = NIL;
	foreach(l, plan->targetlist)
	{
		TargetEntry *tle = (TargetEntry *) lfirst(l);
		Node	   *newexpr;

		newexpr = replace_vars_with_subplan_refs((Node *) tle->expr,
												 subplan_itlist,
												 subvarno);
		tle = flatCopyTargetEntry(tle);
		tle->expr = (Expr *) newexpr;
		output_targetlist = lappend(output_targetlist, tle);
	}
	plan->targetlist = output_targetlist;

	plan->qual = (List *)
		replace_vars_with_subplan_refs((Node *) plan->qual,
									   subplan_itlist,
									   subvarno);

	pfree(subplan_itlist);
}
