cost_bitmap_heap_scan(Path *path, PlannerInfo *root, RelOptInfo *baserel,
					  Path *bitmapqual, RelOptInfo *outer_rel)
{
	Cost		startup_cost = 0;
	Cost		run_cost = 0;
	Cost		indexTotalCost;
	Selectivity indexSelectivity;
	Cost		cpu_per_tuple;
	Cost		cost_per_page;
	double		tuples_fetched;
	double		pages_fetched;
	double		T;


	Assert(IsA(baserel, RelOptInfo));
	Assert(baserel->relid > 0);
	Assert(baserel->rtekind == RTE_RELATION);

	if (!enable_bitmapscan)
		startup_cost += disable_cost;


	cost_bitmap_tree_node(bitmapqual, &indexTotalCost, &indexSelectivity);

	startup_cost += indexTotalCost;


	tuples_fetched = clamp_row_est(indexSelectivity * baserel->tuples);

	T = (baserel->pages > 1) ? (double) baserel->pages : 1.0;

	if (outer_rel != NULL && outer_rel->rows > 1)
	{


		double		num_scans = outer_rel->rows;

		pages_fetched = index_pages_fetched(tuples_fetched * num_scans,
											baserel->pages,
											get_indexpath_pages(bitmapqual),
											root);
		pages_fetched /= num_scans;
	}
	else
	{


		pages_fetched = (2.0 * T * tuples_fetched) / (2.0 * T + tuples_fetched);
	}
	if (pages_fetched >= T)
		pages_fetched = T;
	else
		pages_fetched = ceil(pages_fetched);


	if (pages_fetched >= 2.0)
		cost_per_page = random_page_cost -
			(random_page_cost - seq_page_cost) * sqrt(pages_fetched / T);
	else
		cost_per_page = random_page_cost;

	run_cost += pages_fetched * cost_per_page;


	startup_cost += baserel->baserestrictcost.startup;
	cpu_per_tuple = cpu_tuple_cost + baserel->baserestrictcost.per_tuple;

	run_cost += cpu_per_tuple * tuples_fetched;

	path->startup_cost = startup_cost;
	path->total_cost = startup_cost + run_cost;
}
