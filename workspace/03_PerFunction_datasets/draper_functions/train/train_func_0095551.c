cost_bitmap_and_node(BitmapAndPath *path, PlannerInfo *root)
{
	Cost		totalCost;
	Selectivity selec;
	ListCell   *l;


	totalCost = 0.0;
	selec = 1.0;
	foreach(l, path->bitmapquals)
	{
		Path	   *subpath = (Path *) lfirst(l);
		Cost		subCost;
		Selectivity subselec;

		cost_bitmap_tree_node(subpath, &subCost, &subselec);

		selec *= subselec;

		totalCost += subCost;
		if (l != list_head(path->bitmapquals))
			totalCost += 100.0 * cpu_operator_cost;
	}
	path->bitmapselectivity = selec;
	path->path.startup_cost = totalCost;
	path->path.total_cost = totalCost;
}
