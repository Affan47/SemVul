create_bitmap_scan_plan(PlannerInfo *root,
						BitmapHeapPath *best_path,
						List *tlist,
						List *scan_clauses)
{
	Index		baserelid = best_path->path.parent->relid;
	Plan	   *bitmapqualplan;
	List	   *bitmapqualorig;
	List	   *indexquals;
	List	   *qpqual;
	ListCell   *l;
	BitmapHeapScan *scan_plan;


	Assert(baserelid > 0);
	Assert(best_path->path.parent->rtekind == RTE_RELATION);


	bitmapqualplan = create_bitmap_subplan(root, best_path->bitmapqual,
										   &bitmapqualorig, &indexquals);


	scan_clauses = extract_actual_clauses(scan_clauses, false);


	if (best_path->isjoininner)
	{
		scan_clauses = list_concat_unique(scan_clauses, bitmapqualorig);
	}


	qpqual = NIL;
	foreach(l, scan_clauses)
	{
		Node	   *clause = (Node *) lfirst(l);

		if (list_member(indexquals, clause))
			continue;
		if (!contain_mutable_functions(clause))
		{
			List	   *clausel = list_make1(clause);

			if (predicate_implied_by(clausel, indexquals))
				continue;
		}
		qpqual = lappend(qpqual, clause);
	}


	qpqual = order_qual_clauses(root, qpqual);


	bitmapqualorig = list_difference_ptr(bitmapqualorig, qpqual);


	scan_plan = make_bitmap_heapscan(tlist,
									 qpqual,
									 bitmapqualplan,
									 bitmapqualorig,
									 baserelid);

	copy_path_costsize(&scan_plan->scan.plan, &best_path->path);

	scan_plan->scan.plan.plan_rows = best_path->rows;

	return scan_plan;
}
