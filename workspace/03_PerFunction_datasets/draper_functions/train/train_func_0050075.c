via_lastclose(struct drm_device *dev)
{
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;

	if (!dev_priv)
		return;

	mutex_lock(&dev->struct_mutex);
	if (dev_priv->vram_initialized) {
		drm_mm_takedown(&dev_priv->vram_mm);
		dev_priv->vram_initialized = 0;
	}
	if (dev_priv->agp_initialized) {
		drm_mm_takedown(&dev_priv->agp_mm);
		dev_priv->agp_initialized = 0;
	}
	mutex_unlock(&dev->struct_mutex);
}
