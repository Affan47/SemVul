ApplyRetrieveRule(Query *parsetree,
				  RewriteRule *rule,
				  int rt_index,
				  bool relation_level,
				  Relation relation,
				  List *activeRIRs)
{
	Query	   *rule_action;
	RangeTblEntry *rte,
			   *subrte;
	RowMarkClause *rc;

	if (list_length(rule->actions) != 1)
		elog(ERROR, "expected just one rule action");
	if (rule->qual != NULL)
		elog(ERROR, "cannot handle qualified ON SELECT rule");
	if (!relation_level)
		elog(ERROR, "cannot handle per-attribute ON SELECT rule");


	rule_action = copyObject(linitial(rule->actions));

	AcquireRewriteLocks(rule_action);


	rule_action = fireRIRrules(rule_action, activeRIRs);


	rte = rt_fetch(rt_index, parsetree->rtable);

	rte->rtekind = RTE_SUBQUERY;
	rte->relid = InvalidOid;
	rte->subquery = rule_action;
	rte->inh = false;


	subrte = rt_fetch(PRS2_OLD_VARNO, rule_action->rtable);
	Assert(subrte->relid == relation->rd_id);
	subrte->requiredPerms = rte->requiredPerms;
	subrte->checkAsUser = rte->checkAsUser;
	subrte->selectedCols = rte->selectedCols;
	subrte->modifiedCols = rte->modifiedCols;

	rte->requiredPerms = 0;
	rte->checkAsUser = InvalidOid;
	rte->selectedCols = NULL;
	rte->modifiedCols = NULL;


	if ((rc = get_rowmark(parsetree, rt_index)) != NULL)
	{


		parsetree->rowMarks = list_delete_ptr(parsetree->rowMarks, rc);


		markQueryForLocking(rule_action, (Node *) rule_action->jointree,
							rc->forUpdate, rc->noWait);
	}

	return parsetree;
}
