remove_rel_from_query(PlannerInfo *root, int relid, Relids joinrelids)
{
	RelOptInfo *rel = find_base_rel(root, relid);
	List	   *joininfos;
	Index		rti;
	ListCell   *l;
	ListCell   *nextl;


	rel->reloptkind = RELOPT_DEADREL;


	for (rti = 1; rti < root->simple_rel_array_size; rti++)
	{
		RelOptInfo *otherrel = root->simple_rel_array[rti];
		int			attroff;


		if (otherrel == NULL)
			continue;

		Assert(otherrel->relid == rti);


		if (otherrel == rel)
			continue;

		for (attroff = otherrel->max_attr - otherrel->min_attr;
			 attroff >= 0;
			 attroff--)
		{
			otherrel->attr_needed[attroff] =
				bms_del_member(otherrel->attr_needed[attroff], relid);
		}
	}


	foreach(l, root->join_info_list)
	{
		SpecialJoinInfo *sjinfo = (SpecialJoinInfo *) lfirst(l);

		sjinfo->min_lefthand = bms_del_member(sjinfo->min_lefthand, relid);
		sjinfo->min_righthand = bms_del_member(sjinfo->min_righthand, relid);
		sjinfo->syn_lefthand = bms_del_member(sjinfo->syn_lefthand, relid);
		sjinfo->syn_righthand = bms_del_member(sjinfo->syn_righthand, relid);
	}


	Assert(root->lateral_info_list == NIL);


	for (l = list_head(root->placeholder_list); l != NULL; l = nextl)
	{
		PlaceHolderInfo *phinfo = (PlaceHolderInfo *) lfirst(l);

		nextl = lnext(l);
		Assert(!bms_is_member(relid, phinfo->ph_lateral));
		if (bms_is_subset(phinfo->ph_needed, joinrelids) &&
			bms_is_member(relid, phinfo->ph_eval_at))
			root->placeholder_list = list_delete_ptr(root->placeholder_list,
													 phinfo);
		else
		{
			phinfo->ph_eval_at = bms_del_member(phinfo->ph_eval_at, relid);
			Assert(!bms_is_empty(phinfo->ph_eval_at));
			phinfo->ph_needed = bms_del_member(phinfo->ph_needed, relid);
		}
	}


	joininfos = list_copy(rel->joininfo);
	foreach(l, joininfos)
	{
		RestrictInfo *rinfo = (RestrictInfo *) lfirst(l);

		remove_join_clause_from_rels(root, rinfo, rinfo->required_relids);

		if (rinfo->is_pushed_down ||
			!bms_equal(rinfo->required_relids, joinrelids))
		{

			Assert(!bms_is_member(relid, rinfo->clause_relids));


			rinfo->required_relids = bms_copy(rinfo->required_relids);
			rinfo->required_relids = bms_del_member(rinfo->required_relids,
													relid);
			distribute_restrictinfo_to_rels(root, rinfo);
		}
	}
}
