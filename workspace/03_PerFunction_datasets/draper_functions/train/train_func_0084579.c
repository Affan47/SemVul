radeon_cp_stop(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	drm_radeon_cp_stop_t *stop = data;
	int ret;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (!dev_priv->cp_running)
		return 0;


	if (stop->flush) {
		radeon_do_cp_flush(dev_priv);
	}


	if (stop->idle) {
		if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
			ret = r600_do_cp_idle(dev_priv);
		else
			ret = radeon_do_cp_idle(dev_priv);
		if (ret)
			return ret;
	}


	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
		r600_do_cp_stop(dev_priv);
	else
		radeon_do_cp_stop(dev_priv);


	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
		r600_do_engine_reset(dev);
	else
		radeon_do_engine_reset(dev);

	return 0;
}
