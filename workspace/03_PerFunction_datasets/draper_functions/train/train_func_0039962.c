evrpc_free(struct evrpc_base *base)
{
	struct evrpc *rpc;
	struct evrpc_hook *hook;
	struct evrpc_hook_ctx *pause;
	int r;

	while ((rpc = TAILQ_FIRST(&base->registered_rpcs)) != NULL) {
		r = evrpc_unregister_rpc(base, rpc->uri);
		EVUTIL_ASSERT(r == 0);
	}
	while ((pause = TAILQ_FIRST(&base->paused_requests)) != NULL) {
		TAILQ_REMOVE(&base->paused_requests, pause, next);
		mm_free(pause);
	}
	while ((hook = TAILQ_FIRST(&base->input_hooks)) != NULL) {
		r = evrpc_remove_hook(base, EVRPC_INPUT, hook);
		EVUTIL_ASSERT(r);
	}
	while ((hook = TAILQ_FIRST(&base->output_hooks)) != NULL) {
		r = evrpc_remove_hook(base, EVRPC_OUTPUT, hook);
		EVUTIL_ASSERT(r);
	}
	mm_free(base);
}
