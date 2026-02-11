mga_do_dma_flush(drm_mga_private_t *dev_priv)
{
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;
	u32 head, tail;
	u32 status = 0;
	int i;
	DMA_LOCALS;
	DRM_DEBUG("\n");


	for (i = 0; i < dev_priv->usec_timeout; i++) {
		status = MGA_READ(MGA_STATUS) & MGA_ENGINE_IDLE_MASK;
		if (status == MGA_ENDPRDMASTS)
			break;
		DRM_UDELAY(1);
	}

	if (primary->tail == primary->last_flush) {
		DRM_DEBUG("   bailing out...\n");
		return;
	}

	tail = primary->tail + dev_priv->primary->offset;


	BEGIN_DMA(1);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();

	primary->last_flush = primary->tail;

	head = MGA_READ(MGA_PRIMADDRESS);

	if (head <= tail)
		primary->space = primary->size - primary->tail;
	else
		primary->space = head - tail;

	DRM_DEBUG("   head = 0x%06lx\n", (unsigned long)(head - dev_priv->primary->offset));
	DRM_DEBUG("   tail = 0x%06lx\n", (unsigned long)(tail - dev_priv->primary->offset));
	DRM_DEBUG("  space = 0x%06x\n", primary->space);

	mga_flush_write_combine();
	MGA_WRITE(MGA_PRIMEND, tail | dev_priv->dma_access);

	DRM_DEBUG("done.\n");
}
