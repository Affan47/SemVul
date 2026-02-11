relation_excluded_by_constraints(PlannerInfo *root,
								 RelOptInfo *rel, RangeTblEntry *rte)
{
	List	   *safe_restrictions;
	List	   *constraint_pred;
	List	   *safe_constraints;
	ListCell   *lc;


	if (constraint_exclusion == CONSTRAINT_EXCLUSION_OFF ||
		(constraint_exclusion == CONSTRAINT_EXCLUSION_PARTITION &&
		 !(rel->reloptkind == RELOPT_OTHER_MEMBER_REL ||
		   (root->hasInheritedTarget &&
			rel->reloptkind == RELOPT_BASEREL &&
			rel->relid == root->parse->resultRelation))))
		return false;


	safe_restrictions = NIL;
	foreach(lc, rel->baserestrictinfo)
	{
		RestrictInfo *rinfo = (RestrictInfo *) lfirst(lc);

		if (!contain_mutable_functions((Node *) rinfo->clause))
			safe_restrictions = lappend(safe_restrictions, rinfo->clause);
	}

	if (predicate_refuted_by(safe_restrictions, safe_restrictions))
		return true;


	if (rte->rtekind != RTE_RELATION || rte->inh)
		return false;


	constraint_pred = get_relation_constraints(root, rte->relid, rel, true);


	safe_constraints = NIL;
	foreach(lc, constraint_pred)
	{
		Node	   *pred = (Node *) lfirst(lc);

		if (!contain_mutable_functions(pred))
			safe_constraints = lappend(safe_constraints, pred);
	}


	if (predicate_refuted_by(safe_constraints, rel->baserestrictinfo))
		return true;

	return false;
}
