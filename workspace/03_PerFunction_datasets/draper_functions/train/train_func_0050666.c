transformMinMaxExpr(ParseState *pstate, MinMaxExpr *m)
{
	MinMaxExpr *newm = makeNode(MinMaxExpr);
	List	   *newargs = NIL;
	List	   *newcoercedargs = NIL;
	List	   *typeids = NIL;
	ListCell   *args;

	newm->op = m->op;
	foreach(args, m->args)
	{
		Node	   *e = (Node *) lfirst(args);
		Node	   *newe;

		newe = transformExpr(pstate, e);
		newargs = lappend(newargs, newe);
		typeids = lappend_oid(typeids, exprType(newe));
	}

	newm->minmaxtype = select_common_type(typeids, "GREATEST/LEAST");


	foreach(args, newargs)
	{
		Node	   *e = (Node *) lfirst(args);
		Node	   *newe;

		newe = coerce_to_common_type(pstate, e,
									 newm->minmaxtype,
									 "GREATEST/LEAST");
		newcoercedargs = lappend(newcoercedargs, newe);
	}

	newm->args = newcoercedargs;
	return (Node *) newm;
}
