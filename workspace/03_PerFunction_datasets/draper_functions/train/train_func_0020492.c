push_ancestor_plan(deparse_namespace *dpns, ListCell *ancestor_cell,
				   deparse_namespace *save_dpns)
{
	PlanState  *ps = (PlanState *) lfirst(ancestor_cell);
	List	   *ancestors;


	*save_dpns = *dpns;


	ancestors = NIL;
	while ((ancestor_cell = lnext(ancestor_cell)) != NULL)
		ancestors = lappend(ancestors, lfirst(ancestor_cell));
	dpns->ancestors = ancestors;


	set_deparse_planstate(dpns, ps);
}
