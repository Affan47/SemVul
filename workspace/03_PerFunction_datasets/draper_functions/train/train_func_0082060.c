get_base_rel_indexes(Node *jtnode)
{
	Bitmapset  *result;

	if (jtnode == NULL)
		return NULL;
	if (IsA(jtnode, RangeTblRef))
	{
		int			varno = ((RangeTblRef *) jtnode)->rtindex;

		result = bms_make_singleton(varno);
	}
	else if (IsA(jtnode, FromExpr))
	{
		FromExpr   *f = (FromExpr *) jtnode;
		ListCell   *l;

		result = NULL;
		foreach(l, f->fromlist)
			result = bms_join(result,
							  get_base_rel_indexes(lfirst(l)));
	}
	else if (IsA(jtnode, JoinExpr))
	{
		JoinExpr   *j = (JoinExpr *) jtnode;

		result = bms_join(get_base_rel_indexes(j->larg),
						  get_base_rel_indexes(j->rarg));
	}
	else
	{
		elog(ERROR, "unrecognized node type: %d",
			 (int) nodeTag(jtnode));
		result = NULL;
	}
	return result;
}
