build_joinrel_restrictlist(PlannerInfo *root,
						   RelOptInfo *joinrel,
						   RelOptInfo *outer_rel,
						   RelOptInfo *inner_rel,
						   JoinType jointype)
{
	List	   *result;
	List	   *rlist;


	rlist = list_concat(subbuild_joinrel_restrictlist(joinrel,
													  outer_rel->joininfo),
						subbuild_joinrel_restrictlist(joinrel,
													  inner_rel->joininfo));


	result = remove_redundant_join_clauses(root, rlist,
										   outer_rel->relids,
										   inner_rel->relids,
										   IS_OUTER_JOIN(jointype));

	list_free(rlist);

	return result;
}
