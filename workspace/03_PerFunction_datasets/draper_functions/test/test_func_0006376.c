mga_emit_clip_rect(drm_mga_private_t *dev_priv,
			       struct drm_clip_rect *box)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	unsigned int pitch = dev_priv->front_pitch;
	DMA_LOCALS;

	BEGIN_DMA(2);


	if (dev_priv->chipset >= MGA_CARD_TYPE_G400) {
		DMA_BLOCK(MGA_DWGCTL, ctx->dwgctl,
			  MGA_LEN + MGA_EXEC, 0x80000000,
			  MGA_DWGCTL, ctx->dwgctl,
			  MGA_LEN + MGA_EXEC, 0x80000000);
	}
	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_CXBNDRY, ((box->x2 - 1) << 16) | box->x1,
		  MGA_YTOP, box->y1 * pitch, MGA_YBOT, (box->y2 - 1) * pitch);

	ADVANCE_DMA();
}
