show_scan_qual(List *qual, const char *qlabel,
			   int scanrelid, Plan *outer_plan, Plan *inner_plan,
			   StringInfo str, int indent, ExplainState *es)
{
	List	   *context;
	bool		useprefix;
	Node	   *node;
	char	   *exprstr;
	int			i;


	if (qual == NIL)
		return;


	node = (Node *) make_ands_explicit(qual);


	context = deparse_context_for_plan((Node *) outer_plan,
									   (Node *) inner_plan,
									   es->rtable);
	useprefix = (outer_plan != NULL || inner_plan != NULL);


	exprstr = deparse_expression(node, context, useprefix, false);


	for (i = 0; i < indent; i++)
		appendStringInfo(str, "  ");
	appendStringInfo(str, "  %s: %s\n", qlabel, exprstr);
}
