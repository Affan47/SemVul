r128_do_init_pageflip(struct drm_device *dev)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	DRM_DEBUG("\n");

	dev_priv->crtc_offset = R128_READ(R128_CRTC_OFFSET);
	dev_priv->crtc_offset_cntl = R128_READ(R128_CRTC_OFFSET_CNTL);

	R128_WRITE(R128_CRTC_OFFSET, dev_priv->front_offset);
	R128_WRITE(R128_CRTC_OFFSET_CNTL,
		   dev_priv->crtc_offset_cntl | R128_CRTC_OFFSET_FLIP_CNTL);

	dev_priv->page_flipping = 1;
	dev_priv->current_page = 0;
	dev_priv->sarea_priv->pfCurrentPage = dev_priv->current_page;

	return 0;
}
