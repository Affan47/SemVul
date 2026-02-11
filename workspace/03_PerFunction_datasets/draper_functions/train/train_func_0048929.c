check_hazardous_phv(PlannerInfo *root,
					Path *outer_path,
					Path *inner_path)
{
	Relids		innerparams = PATH_REQ_OUTER(inner_path);
	Relids		outerrelids = outer_path->parent->relids;
	ListCell   *lc;

	foreach(lc, root->placeholder_list)
	{
		PlaceHolderInfo *phinfo = (PlaceHolderInfo *) lfirst(lc);

		if (!bms_is_subset(phinfo->ph_eval_at, innerparams))
			continue;
		if (!bms_overlap(phinfo->ph_eval_at, outerrelids))
			continue;
		if (bms_is_subset(phinfo->ph_eval_at, outerrelids))
			continue;

		return false;
	}


	return true;
}
