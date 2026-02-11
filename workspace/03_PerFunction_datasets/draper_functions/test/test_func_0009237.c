evrpc_pause_request(void *vbase, void *ctx,
    void (*cb)(void *, enum EVRPC_HOOK_RESULT))
{
	struct _evrpc_hooks *base = vbase;
	struct evrpc_hook_ctx *pause = mm_malloc(sizeof(*pause));
	if (pause == NULL)
		return (-1);

	pause->ctx = ctx;
	pause->cb = cb;

	TAILQ_INSERT_TAIL(&base->pause_requests, pause, next);
	return (0);
}
