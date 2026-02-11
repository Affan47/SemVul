cost_seqscan(Path *path, PlannerInfo *root,
			 RelOptInfo *baserel)
{
	Cost		startup_cost = 0;
	Cost		run_cost = 0;
	Cost		cpu_per_tuple;


	Assert(baserel->relid > 0);
	Assert(baserel->rtekind == RTE_RELATION);

	if (!enable_seqscan)
		startup_cost += disable_cost;


	run_cost += seq_page_cost * baserel->pages;


	startup_cost += baserel->baserestrictcost.startup;
	cpu_per_tuple = cpu_tuple_cost + baserel->baserestrictcost.per_tuple;
	run_cost += cpu_per_tuple * baserel->tuples;

	path->startup_cost = startup_cost;
	path->total_cost = startup_cost + run_cost;
}
