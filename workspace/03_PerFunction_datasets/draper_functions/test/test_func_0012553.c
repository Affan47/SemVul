install_handler_block_guard (MonoJitInfo *ji, MonoContext *ctx)
{
	int i;
	MonoJitExceptionInfo *clause = NULL;
	gpointer ip;

	ip = MONO_CONTEXT_GET_IP (ctx);

	for (i = 0; i < ji->num_clauses; ++i) {
		clause = &ji->clauses [i];
		if (clause->flags != MONO_EXCEPTION_CLAUSE_FINALLY)
			continue;
		if (clause->handler_start < ip && clause->data.handler_end > ip)
			break;
	}


	if (i == ji->num_clauses)
		return NULL;


	if (ip == clause->handler_start)
		return NULL;

	return mono_arch_install_handler_block_guard (ji, clause, ctx, mono_create_handler_block_trampoline ());
}
