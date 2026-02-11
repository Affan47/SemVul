mga_dma_iload(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	struct drm_device_dma *dma = dev->dma;
	drm_mga_private_t *dev_priv = dev->dev_private;
	struct drm_buf *buf;
	drm_mga_buf_priv_t *buf_priv;
	drm_mga_iload_t *iload = data;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

#if 0
	if (mga_do_wait_for_idle(dev_priv) < 0) {
		if (MGA_DMA_DEBUG)
			DRM_INFO("-EBUSY\n");
		return -EBUSY;
	}
#endif
	if (iload->idx < 0 || iload->idx > dma->buf_count)
		return -EINVAL;

	buf = dma->buflist[iload->idx];
	buf_priv = buf->dev_private;

	if (mga_verify_iload(dev_priv, iload->dstorg, iload->length)) {
		mga_freelist_put(dev, buf);
		return -EINVAL;
	}

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_iload(dev, buf, iload->dstorg, iload->length);


	dev_priv->sarea_priv->dirty |= MGA_UPLOAD_CONTEXT;

	return 0;
}
