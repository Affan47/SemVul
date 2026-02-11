udl_detach_dma_buf(struct dma_buf *dmabuf,
			       struct dma_buf_attachment *attach)
{
	struct udl_drm_dmabuf_attachment *udl_attach = attach->priv;
	struct sg_table *sgt;

	if (!udl_attach)
		return;

	DRM_DEBUG_PRIME("[DEV:%s] size:%zd\n", dev_name(attach->dev),
			attach->dmabuf->size);

	sgt = &udl_attach->sgt;

	if (udl_attach->dir != DMA_NONE)
		dma_unmap_sg(attach->dev, sgt->sgl, sgt->nents,
				udl_attach->dir);

	sg_free_table(sgt);
	kfree(udl_attach);
	attach->priv = NULL;
}
