fix_scan_expr_walker(Node *node, fix_scan_expr_context *context)
{
	if (node == NULL)
		return false;
	if (IsA(node, OpExpr))
		set_opfuncid((OpExpr *) node);
	else if (IsA(node, DistinctExpr))
		set_opfuncid((OpExpr *) node);
	else if (IsA(node, NullIfExpr))
		set_opfuncid((OpExpr *) node);
	else if (IsA(node, ScalarArrayOpExpr))
		set_sa_opfuncid((ScalarArrayOpExpr *) node);
	else if (IsA(node, Const))
	{
		Const	   *con = (Const *) node;


		if (ISREGCLASSCONST(con))
			context->glob->relationOids =
				lappend_oid(context->glob->relationOids,
							DatumGetObjectId(con->constvalue));
		return false;
	}
	return expression_tree_walker(node, fix_scan_expr_walker,
								  (void *) context);
}
