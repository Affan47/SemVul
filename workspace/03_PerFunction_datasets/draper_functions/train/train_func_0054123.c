mga_g400_emit_context(drm_mga_private_t *dev_priv)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	DMA_LOCALS;

	BEGIN_DMA(4);

	DMA_BLOCK(MGA_DSTORG, ctx->dstorg,
		  MGA_MACCESS, ctx->maccess,
		  MGA_PLNWT, ctx->plnwt, MGA_DWGCTL, ctx->dwgctl);

	DMA_BLOCK(MGA_ALPHACTRL, ctx->alphactrl,
		  MGA_FOGCOL, ctx->fogcolor,
		  MGA_WFLAG, ctx->wflag, MGA_ZORG, dev_priv->depth_offset);

	DMA_BLOCK(MGA_WFLAG1, ctx->wflag,
		  MGA_TDUALSTAGE0, ctx->tdualstage0,
		  MGA_TDUALSTAGE1, ctx->tdualstage1, MGA_FCOL, ctx->fcol);

	DMA_BLOCK(MGA_STENCIL, ctx->stencil,
		  MGA_STENCILCTL, ctx->stencilctl,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();
}
