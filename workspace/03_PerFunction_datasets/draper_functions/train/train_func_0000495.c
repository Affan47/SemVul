mgag200_modeset_init(struct mga_device *mdev)
{
	struct drm_encoder *encoder;
	struct drm_connector *connector;
	int ret;

	mdev->mode_info.mode_config_initialized = true;

	mdev->dev->mode_config.max_width = MGAG200_MAX_FB_WIDTH;
	mdev->dev->mode_config.max_height = MGAG200_MAX_FB_HEIGHT;

	mdev->dev->mode_config.fb_base = mdev->mc.vram_base;

	mga_crtc_init(mdev);

	encoder = mga_encoder_init(mdev->dev);
	if (!encoder) {
		DRM_ERROR("mga_encoder_init failed\n");
		return -1;
	}

	connector = mga_vga_init(mdev->dev);
	if (!connector) {
		DRM_ERROR("mga_vga_init failed\n");
		return -1;
	}

	drm_mode_connector_attach_encoder(connector, encoder);

	ret = mgag200_fbdev_init(mdev);
	if (ret) {
		DRM_ERROR("mga_fbdev_init failed\n");
		return ret;
	}

	return 0;
}
