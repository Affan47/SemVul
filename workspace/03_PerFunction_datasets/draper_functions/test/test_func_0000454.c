evrpc_make_request(struct evrpc_request_wrapper *ctx)
{
	struct evrpc_pool *pool = ctx->pool;


	evtimer_assign(&ctx->ev_timeout, pool->base, evrpc_request_timeout, ctx);


	EVUTIL_ASSERT(TAILQ_FIRST(&pool->connections) != NULL);


	TAILQ_INSERT_TAIL(&pool->requests, ctx, next);

	evrpc_pool_schedule(pool);

	return (0);
}
