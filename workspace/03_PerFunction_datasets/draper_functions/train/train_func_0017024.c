resolvenew_in_jointree(Node *jtnode, int varno,
					   RangeTblEntry *rte, List *subtlist)
{
	if (jtnode == NULL)
		return;
	if (IsA(jtnode, RangeTblRef))
	{

	}
	else if (IsA(jtnode, FromExpr))
	{
		FromExpr   *f = (FromExpr *) jtnode;
		ListCell   *l;

		foreach(l, f->fromlist)
			resolvenew_in_jointree(lfirst(l), varno, rte, subtlist);
		f->quals = ResolveNew(f->quals,
							  varno, 0, rte,
							  subtlist, CMD_SELECT, 0);
	}
	else if (IsA(jtnode, JoinExpr))
	{
		JoinExpr   *j = (JoinExpr *) jtnode;

		resolvenew_in_jointree(j->larg, varno, rte, subtlist);
		resolvenew_in_jointree(j->rarg, varno, rte, subtlist);
		j->quals = ResolveNew(j->quals,
							  varno, 0, rte,
							  subtlist, CMD_SELECT, 0);


	}
	else
		elog(ERROR, "unrecognized node type: %d",
			 (int) nodeTag(jtnode));
}
