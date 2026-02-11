find_nots(Expr *qual)
{
	if (and_clause((Node *) qual))
	{
		List	   *t_list = NIL;
		ListCell   *temp;

		foreach(temp, ((BoolExpr *) qual)->args)
			t_list = lappend(t_list, find_nots(lfirst(temp)));
		return make_andclause(pull_ands(t_list));
	}
	else if (or_clause((Node *) qual))
	{
		List	   *t_list = NIL;
		ListCell   *temp;

		foreach(temp, ((BoolExpr *) qual)->args)
			t_list = lappend(t_list, find_nots(lfirst(temp)));
		return make_orclause(pull_ors(t_list));
	}
	else if (not_clause((Node *) qual))
		return push_nots(get_notclausearg(qual));
	else
		return qual;
}
