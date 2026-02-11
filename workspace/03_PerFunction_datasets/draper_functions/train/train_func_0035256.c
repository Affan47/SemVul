ast_unregister_switch(struct ast_switch *sw)
{
	AST_RWLIST_WRLOCK(&switches);
	AST_RWLIST_REMOVE(&switches, sw, list);
	AST_RWLIST_UNLOCK(&switches);
}
