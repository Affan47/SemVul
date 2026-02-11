i810_dma_mc(struct drm_device *dev, void *data,
		       struct drm_file *file_priv)
{
	struct drm_device_dma *dma = dev->dma;
	drm_i810_private_t *dev_priv = (drm_i810_private_t *) dev->dev_private;
	u32 *hw_status = dev_priv->hw_status_page;
	drm_i810_sarea_t *sarea_priv = (drm_i810_sarea_t *)
	    dev_priv->sarea_priv;
	drm_i810_mc_t *mc = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (mc->idx >= dma->buf_count || mc->idx < 0)
		return -EINVAL;

	i810_dma_dispatch_mc(dev, dma->buflist[mc->idx], mc->used,
			     mc->last_render);

	sarea_priv->last_enqueue = dev_priv->counter - 1;
	sarea_priv->last_dispatch = (int)hw_status[5];

	return 0;
}
