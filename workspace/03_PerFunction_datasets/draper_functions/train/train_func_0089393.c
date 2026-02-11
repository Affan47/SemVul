mem_getstats(isc__mem_t *ctx, size_t size) {
	ctx->total += size;
	ctx->inuse += size;

	if (size > ctx->max_size) {
		ctx->stats[ctx->max_size].gets++;
		ctx->stats[ctx->max_size].totalgets++;
	} else {
		ctx->stats[size].gets++;
		ctx->stats[size].totalgets++;
	}
}
