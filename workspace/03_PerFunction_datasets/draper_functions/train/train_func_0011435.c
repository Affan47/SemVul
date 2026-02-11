i810_flip_bufs(struct drm_device *dev, void *data,
			  struct drm_file *file_priv)
{
	drm_i810_private_t *dev_priv = dev->dev_private;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (!dev_priv->page_flipping)
		i810_do_init_pageflip(dev);

	i810_dma_dispatch_flip(dev);
	return 0;
}
