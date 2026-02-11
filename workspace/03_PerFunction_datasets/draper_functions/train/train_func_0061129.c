show_qual(List *qual, const char *qlabel,
		  PlanState *planstate, List *ancestors,
		  bool useprefix, ExplainState *es)
{
	Node	   *node;


	if (qual == NIL)
		return;


	node = (Node *) make_ands_explicit(qual);


	show_expression(node, qlabel, planstate, ancestors, useprefix, es);
}
