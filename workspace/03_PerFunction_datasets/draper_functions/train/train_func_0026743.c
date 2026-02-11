xgc_freelist_inc(size_t idx, struct xgc_context *xgctx)
{
	xgctx->available[idx]--;
	xgctx->count[idx]++;
	if G_UNLIKELY(xgctx->largest < xgctx->count[idx])
		xgctx->largest = xgctx->count[idx];
}
