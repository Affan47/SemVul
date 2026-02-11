nv50_gr_construct_gene_eng2d(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;


	xf_emit(ctx, 2, 0);
	xf_emit(ctx, 2, 0);
	xf_emit(ctx, 1, 0);
	if (device->chipset < 0xa0) {


		xf_emit(ctx, 2, 0);
		xf_emit(ctx, 2, 1);
		xf_emit(ctx, 1, 0);
	}
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 0x100);
	xf_emit(ctx, 1, 0x100);
	xf_emit(ctx, 1, 0x11);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 8);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 0xcf);
	xf_emit(ctx, 1, 2);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 4);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 1);
	xf_emit(ctx, 1, 0x15);
	xf_emit(ctx, 2, 0);
	xf_emit(ctx, 1, 0);
	xf_emit(ctx, 1, 0x4444480);

	xf_emit(ctx, 0x10, 0);

	xf_emit(ctx, 0x27, 0);
}
