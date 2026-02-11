create_functionscan_plan(PlannerInfo *root, Path *best_path,
						 List *tlist, List *scan_clauses)
{
	FunctionScan *scan_plan;
	Index		scan_relid = best_path->parent->relid;
	RangeTblEntry *rte;


	Assert(scan_relid > 0);
	rte = planner_rt_fetch(scan_relid, root);
	Assert(rte->rtekind == RTE_FUNCTION);


	scan_clauses = order_qual_clauses(root, scan_clauses);


	scan_clauses = extract_actual_clauses(scan_clauses, false);

	scan_plan = make_functionscan(tlist, scan_clauses, scan_relid,
								  rte->funcexpr,
								  rte->eref->colnames,
								  rte->funccoltypes,
								  rte->funccoltypmods,
								  rte->funccolcollations);

	copy_path_costsize(&scan_plan->scan.plan, best_path);

	return scan_plan;
}
