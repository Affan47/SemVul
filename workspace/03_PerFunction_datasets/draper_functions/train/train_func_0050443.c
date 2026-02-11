cost_windowagg(Path *path, PlannerInfo *root,
			   List *windowFuncs, int numPartCols, int numOrderCols,
			   Cost input_startup_cost, Cost input_total_cost,
			   double input_tuples)
{
	Cost		startup_cost;
	Cost		total_cost;
	ListCell   *lc;

	startup_cost = input_startup_cost;
	total_cost = input_total_cost;


	foreach(lc, windowFuncs)
	{
		WindowFunc *wfunc = (WindowFunc *) lfirst(lc);
		Cost		wfunccost;
		QualCost	argcosts;

		Assert(IsA(wfunc, WindowFunc));

		wfunccost = get_func_cost(wfunc->winfnoid) * cpu_operator_cost;


		cost_qual_eval_node(&argcosts, (Node *) wfunc->args, root);
		startup_cost += argcosts.startup;
		wfunccost += argcosts.per_tuple;


		cost_qual_eval_node(&argcosts, (Node *) wfunc->aggfilter, root);
		startup_cost += argcosts.startup;
		wfunccost += argcosts.per_tuple;

		total_cost += wfunccost * input_tuples;
	}


	total_cost += cpu_operator_cost * (numPartCols + numOrderCols) * input_tuples;
	total_cost += cpu_tuple_cost * input_tuples;

	path->rows = input_tuples;
	path->startup_cost = startup_cost;
	path->total_cost = total_cost;
}
