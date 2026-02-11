guess_pool_from_qkdata(void *host, void *value, size_t len, void *data)
{
	struct guess_load_context *ctx = data;
	struct qkdata *qk = value;
	guess_t *gq = ctx->gq;

	g_assert(len == sizeof *qk);


	if (
		!hset_contains(gq->queried, host) &&
		!hash_list_contains(gq->pool, host)
	) {
		hash_list_append(gq->pool, atom_host_get(host));
		ctx->loaded++;
	}
}
