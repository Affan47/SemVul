create_index_paths(PlannerInfo *root, RelOptInfo *rel)
{
	List	   *indexpaths;
	List	   *bitindexpaths;
	ListCell   *l;


	if (rel->indexlist == NIL)
	{
		rel->index_outer_relids = NULL;
		return;
	}


	rel->index_outer_relids = indexable_outerrelids(root, rel);


	indexpaths = find_usable_indexes(root, rel,
									 rel->baserestrictinfo, NIL,
									 true, NULL, SAOP_FORBID, ST_ANYSCAN);


	bitindexpaths = NIL;
	foreach(l, indexpaths)
	{
		IndexPath  *ipath = (IndexPath *) lfirst(l);

		if (ipath->indexinfo->amhasgettuple)
			add_path(rel, (Path *) ipath);

		if (ipath->indexinfo->amhasgetbitmap &&
			ipath->indexselectivity < 1.0 &&
			!ScanDirectionIsBackward(ipath->indexscandir))
			bitindexpaths = lappend(bitindexpaths, ipath);
	}


	indexpaths = generate_bitmap_or_paths(root, rel,
										  rel->baserestrictinfo, NIL,
										  NULL);
	bitindexpaths = list_concat(bitindexpaths, indexpaths);


	indexpaths = find_saop_paths(root, rel,
								 rel->baserestrictinfo, NIL,
								 true, NULL);
	bitindexpaths = list_concat(bitindexpaths, indexpaths);


	if (bitindexpaths != NIL)
	{
		Path	   *bitmapqual;
		BitmapHeapPath *bpath;

		bitmapqual = choose_bitmap_and(root, rel, bitindexpaths, NULL);
		bpath = create_bitmap_heap_path(root, rel, bitmapqual, NULL);
		add_path(rel, (Path *) bpath);
	}
}
