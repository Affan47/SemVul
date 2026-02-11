dd_emit(struct nvkm_grctx *ctx, int num, u32 val) {
	int i;
	if (val && ctx->mode == NVKM_GRCTX_VALS) {
		for (i = 0; i < num; i++)
			nvkm_wo32(ctx->data, 4 * (ctx->ctxvals_pos + i), val);
	}
	ctx->ctxvals_pos += num;
}
