ast_walk_context_switches(struct ast_context *con,
	struct ast_sw *sw)
{
	if (!sw)
		return con ? AST_LIST_FIRST(&con->alts) : NULL;
	else
		return AST_LIST_NEXT(sw, list);
}
