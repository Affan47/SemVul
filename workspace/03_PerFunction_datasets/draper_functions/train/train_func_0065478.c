vmw_kms_stdu_init_display(struct vmw_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	int i, ret;


	if (!VMWGFX_ENABLE_SCREEN_TARGET_OTABLE)
		return -ENOSYS;

	if (!(dev_priv->capabilities & SVGA_CAP_GBOBJECTS))
		return -ENOSYS;

	ret = drm_vblank_init(dev, VMWGFX_NUM_DISPLAY_UNITS);
	if (unlikely(ret != 0))
		return ret;

	ret = drm_mode_create_dirty_info_property(dev);
	if (unlikely(ret != 0))
		goto err_vblank_cleanup;

	dev_priv->active_display_unit = vmw_du_screen_target;

	for (i = 0; i < VMWGFX_NUM_DISPLAY_UNITS; ++i) {
		ret = vmw_stdu_init(dev_priv, i);

		if (unlikely(ret != 0)) {
			DRM_ERROR("Failed to initialize STDU %d", i);
			goto err_vblank_cleanup;
		}
	}

	DRM_INFO("Screen Target Display device initialized\n");

	return 0;

err_vblank_cleanup:
	drm_vblank_cleanup(dev);
	return ret;
}
