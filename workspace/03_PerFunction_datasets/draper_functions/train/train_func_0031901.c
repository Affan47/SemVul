expr_stack_pop (GSList **pstack)
{
	const GnmExpr *expr;
	GSList *next;

	g_return_val_if_fail (pstack != NULL, NULL);

	expr = (*pstack)->data;
	next = (*pstack)->next;

	g_slist_free_1 (*pstack);

	*pstack = next;
	return expr;
}
