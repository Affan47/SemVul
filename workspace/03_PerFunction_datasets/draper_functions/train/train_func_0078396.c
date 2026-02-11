choose_hashed_distinct(PlannerInfo *root,
					   double tuple_fraction, double limit_tuples,
					   double path_rows, int path_width,
					   Cost cheapest_startup_cost, Cost cheapest_total_cost,
					   Cost sorted_startup_cost, Cost sorted_total_cost,
					   List *sorted_pathkeys,
					   double dNumDistinctRows)
{
	Query	   *parse = root->parse;
	int			numDistinctCols = list_length(parse->distinctClause);
	bool		can_sort;
	bool		can_hash;
	Size		hashentrysize;
	List	   *current_pathkeys;
	List	   *needed_pathkeys;
	Path		hashed_p;
	Path		sorted_p;


	can_sort = grouping_is_sortable(parse->distinctClause);
	if (can_sort && parse->hasDistinctOn)
		return false;

	can_hash = grouping_is_hashable(parse->distinctClause);


	if (!(can_hash && can_sort))
	{
		if (can_hash)
			return true;
		else if (can_sort)
			return false;
		else
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("could not implement DISTINCT"),
					 errdetail("Some of the datatypes only support hashing, while others only support sorting.")));
	}


	if (!enable_hashagg)
		return false;


	hashentrysize = MAXALIGN(path_width) + MAXALIGN(sizeof(MinimalTupleData));

	if (hashentrysize * dNumDistinctRows > work_mem * 1024L)
		return false;


	cost_agg(&hashed_p, root, AGG_HASHED, 0,
			 numDistinctCols, dNumDistinctRows,
			 cheapest_startup_cost, cheapest_total_cost,
			 path_rows);


	if (parse->sortClause)
		cost_sort(&hashed_p, root, root->sort_pathkeys, hashed_p.total_cost,
				  dNumDistinctRows, path_width, limit_tuples);


	sorted_p.startup_cost = sorted_startup_cost;
	sorted_p.total_cost = sorted_total_cost;
	current_pathkeys = sorted_pathkeys;
	if (parse->hasDistinctOn &&
		list_length(root->distinct_pathkeys) <
		list_length(root->sort_pathkeys))
		needed_pathkeys = root->sort_pathkeys;
	else
		needed_pathkeys = root->distinct_pathkeys;
	if (!pathkeys_contained_in(needed_pathkeys, current_pathkeys))
	{
		if (list_length(root->distinct_pathkeys) >=
			list_length(root->sort_pathkeys))
			current_pathkeys = root->distinct_pathkeys;
		else
			current_pathkeys = root->sort_pathkeys;
		cost_sort(&sorted_p, root, current_pathkeys, sorted_p.total_cost,
				  path_rows, path_width, -1.0);
	}
	cost_group(&sorted_p, root, numDistinctCols, dNumDistinctRows,
			   sorted_p.startup_cost, sorted_p.total_cost,
			   path_rows);
	if (parse->sortClause &&
		!pathkeys_contained_in(root->sort_pathkeys, current_pathkeys))
		cost_sort(&sorted_p, root, root->sort_pathkeys, sorted_p.total_cost,
				  dNumDistinctRows, path_width, limit_tuples);


	if (tuple_fraction >= 1.0)
		tuple_fraction /= dNumDistinctRows;

	if (compare_fractional_path_costs(&hashed_p, &sorted_p,
									  tuple_fraction) < 0)
	{

		return true;
	}
	return false;
}
