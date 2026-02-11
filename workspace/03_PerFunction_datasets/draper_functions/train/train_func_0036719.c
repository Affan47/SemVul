MJExamineQuals(List *mergeclauses,
			   Oid *mergefamilies,
			   int *mergestrategies,
			   bool *mergenullsfirst,
			   PlanState *parent)
{
	MergeJoinClause clauses;
	int			nClauses = list_length(mergeclauses);
	int			iClause;
	ListCell   *cl;

	clauses = (MergeJoinClause) palloc0(nClauses * sizeof(MergeJoinClauseData));

	iClause = 0;
	foreach(cl, mergeclauses)
	{
		OpExpr	   *qual = (OpExpr *) lfirst(cl);
		MergeJoinClause clause = &clauses[iClause];
		Oid			opfamily = mergefamilies[iClause];
		StrategyNumber opstrategy = mergestrategies[iClause];
		bool		nulls_first = mergenullsfirst[iClause];
		int			op_strategy;
		Oid			op_lefttype;
		Oid			op_righttype;
		bool		op_recheck;
		RegProcedure cmpproc;
		AclResult	aclresult;

		if (!IsA(qual, OpExpr))
			elog(ERROR, "mergejoin clause is not an OpExpr");


		clause->lexpr = ExecInitExpr((Expr *) linitial(qual->args), parent);
		clause->rexpr = ExecInitExpr((Expr *) lsecond(qual->args), parent);


		get_op_opfamily_properties(qual->opno, opfamily,
								   &op_strategy,
								   &op_lefttype,
								   &op_righttype,
								   &op_recheck);
		if (op_strategy != BTEqualStrategyNumber)
			elog(ERROR, "cannot merge using non-equality operator %u",
				 qual->opno);
		Assert(!op_recheck);


		cmpproc = get_opfamily_proc(opfamily,
									op_lefttype,
									op_righttype,
									BTORDER_PROC);
		if (!RegProcedureIsValid(cmpproc))
			elog(ERROR, "missing support function %d(%u,%u) in opfamily %u",
				 BTORDER_PROC, op_lefttype, op_righttype, opfamily);


		aclresult = pg_proc_aclcheck(cmpproc, GetUserId(), ACL_EXECUTE);
		if (aclresult != ACLCHECK_OK)
			aclcheck_error(aclresult, ACL_KIND_PROC,
						   get_func_name(cmpproc));


		fmgr_info(cmpproc, &(clause->cmpfinfo));


		if (opstrategy == BTLessStrategyNumber)
			clause->reverse = false;
		else if (opstrategy == BTGreaterStrategyNumber)
			clause->reverse = true;
		else
			elog(ERROR, "unsupported mergejoin strategy %d", opstrategy);

		clause->nulls_first = nulls_first;

		iClause++;
	}

	return clauses;
}
