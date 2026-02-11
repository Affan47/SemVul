r600_nomm_get_vb(struct drm_device *dev)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	dev_priv->blit_vb = radeon_freelist_get(dev);
	if (!dev_priv->blit_vb) {
		DRM_ERROR("Unable to allocate vertex buffer for blit\n");
		return -EAGAIN;
	}
	return 0;
}
