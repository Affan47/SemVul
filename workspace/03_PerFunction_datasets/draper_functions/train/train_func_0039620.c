mga_dma_blit(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_blit_t *blit = data;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (sarea_priv->nbox > MGA_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = MGA_NR_SAREA_CLIPRECTS;

	if (mga_verify_blit(dev_priv, blit->srcorg, blit->dstorg))
		return -EINVAL;

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_blit(dev, blit);


	dev_priv->sarea_priv->dirty |= MGA_UPLOAD_CONTEXT;

	return 0;
}
