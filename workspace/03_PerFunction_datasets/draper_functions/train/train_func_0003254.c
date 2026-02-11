cost_samplescan(Path *path, PlannerInfo *root,
				RelOptInfo *baserel, ParamPathInfo *param_info)
{
	Cost		startup_cost = 0;
	Cost		run_cost = 0;
	RangeTblEntry *rte;
	TableSampleClause *tsc;
	TsmRoutine *tsm;
	double		spc_seq_page_cost,
				spc_random_page_cost,
				spc_page_cost;
	QualCost	qpqual_cost;
	Cost		cpu_per_tuple;


	Assert(baserel->relid > 0);
	rte = planner_rt_fetch(baserel->relid, root);
	Assert(rte->rtekind == RTE_RELATION);
	tsc = rte->tablesample;
	Assert(tsc != NULL);
	tsm = GetTsmRoutine(tsc->tsmhandler);


	if (param_info)
		path->rows = param_info->ppi_rows;
	else
		path->rows = baserel->rows;


	get_tablespace_page_costs(baserel->reltablespace,
							  &spc_random_page_cost,
							  &spc_seq_page_cost);


	spc_page_cost = (tsm->NextSampleBlock != NULL) ?
		spc_random_page_cost : spc_seq_page_cost;


	run_cost += spc_page_cost * baserel->pages;


	get_restriction_qual_cost(root, baserel, param_info, &qpqual_cost);

	startup_cost += qpqual_cost.startup;
	cpu_per_tuple = cpu_tuple_cost + qpqual_cost.per_tuple;
	run_cost += cpu_per_tuple * baserel->tuples;

	path->startup_cost = startup_cost;
	path->total_cost = startup_cost + run_cost;
}
