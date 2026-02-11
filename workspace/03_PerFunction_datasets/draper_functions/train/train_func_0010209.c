find_mergeclauses_for_pathkeys(PlannerInfo *root,
							   List *pathkeys,
							   bool outer_keys,
							   List *restrictinfos)
{
	List	   *mergeclauses = NIL;
	ListCell   *i;


	foreach(i, restrictinfos)
	{
		RestrictInfo *rinfo = (RestrictInfo *) lfirst(i);

		cache_mergeclause_eclasses(root, rinfo);
	}

	foreach(i, pathkeys)
	{
		PathKey    *pathkey = (PathKey *) lfirst(i);
		EquivalenceClass *pathkey_ec = pathkey->pk_eclass;
		List	   *matched_restrictinfos = NIL;
		ListCell   *j;


		foreach(j, restrictinfos)
		{
			RestrictInfo *rinfo = (RestrictInfo *) lfirst(j);
			EquivalenceClass *clause_ec;

			if (outer_keys)
				clause_ec = rinfo->outer_is_left ?
					rinfo->left_ec : rinfo->right_ec;
			else
				clause_ec = rinfo->outer_is_left ?
					rinfo->right_ec : rinfo->left_ec;
			if (clause_ec == pathkey_ec)
				matched_restrictinfos = lappend(matched_restrictinfos, rinfo);
		}


		if (matched_restrictinfos == NIL)
			break;


		mergeclauses = list_concat(mergeclauses, matched_restrictinfos);
	}

	return mergeclauses;
}
