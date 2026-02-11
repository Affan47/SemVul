sched_alloc(struct ast_sched_context *con)
{
	struct sched *tmp;


#ifdef SCHED_MAX_CACHE
	if ((tmp = AST_LIST_REMOVE_HEAD(&con->schedc, list)))
		con->schedccnt--;
	else
#endif
		tmp = ast_calloc(1, sizeof(*tmp));

	return tmp;
}
