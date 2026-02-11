create_or_index_quals(PlannerInfo *root, RelOptInfo *rel)
{
	BitmapOrPath *bestpath = NULL;
	RestrictInfo *bestrinfo = NULL;
	List	   *newrinfos;
	RestrictInfo *or_rinfo;
	Selectivity or_selec,
				orig_selec;
	ListCell   *i;


	foreach(i, rel->joininfo)
	{
		RestrictInfo *rinfo = (RestrictInfo *) lfirst(i);

		if (restriction_is_or_clause(rinfo) &&
			rinfo->is_pushed_down &&
			!bms_is_member(rel->relid, rinfo->nullable_relids))
		{


			List	   *orpaths;
			ListCell   *k;

			orpaths = generate_bitmap_or_paths(root, rel,
											   list_make1(rinfo),
											   rel->baserestrictinfo,
											   NULL);


			foreach(k, orpaths)
			{
				BitmapOrPath *path = (BitmapOrPath *) lfirst(k);

				Assert(IsA(path, BitmapOrPath));
				if (bestpath == NULL ||
					path->path.total_cost < bestpath->path.total_cost)
				{
					bestpath = path;
					bestrinfo = rinfo;
				}
			}
		}
	}


	if (bestpath == NULL)
		return false;


	newrinfos = make_restrictinfo_from_bitmapqual((Path *) bestpath,
												  true, true);


	if (list_length(newrinfos) != 1)
		return false;
	or_rinfo = (RestrictInfo *) linitial(newrinfos);
	Assert(IsA(or_rinfo, RestrictInfo));
	if (!restriction_is_or_clause(or_rinfo))
		return false;


	rel->baserestrictinfo = list_concat(rel->baserestrictinfo, newrinfos);


	or_selec = clause_selectivity(root, (Node *) or_rinfo,
								  0, JOIN_INNER, NULL);
	if (or_selec > 0 && or_selec < 1)
	{
		orig_selec = clause_selectivity(root, (Node *) bestrinfo,
										0, JOIN_INNER, NULL);
		bestrinfo->norm_selec = orig_selec / or_selec;

		if (bestrinfo->norm_selec > 1)
			bestrinfo->norm_selec = 1;

	}


	return true;
}
