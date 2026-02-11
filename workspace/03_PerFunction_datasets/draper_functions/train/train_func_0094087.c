radeon_fbdev_init(struct radeon_device *rdev)
{
	struct radeon_fbdev *rfbdev;
	int bpp_sel = 32;
	int ret;


	if (list_empty(&rdev->ddev->mode_config.connector_list))
		return 0;


	if (ASIC_IS_RN50(rdev) || rdev->mc.real_vram_size <= (32*1024*1024))
		bpp_sel = 8;

	rfbdev = kzalloc(sizeof(struct radeon_fbdev), GFP_KERNEL);
	if (!rfbdev)
		return -ENOMEM;

	rfbdev->rdev = rdev;
	rdev->mode_info.rfbdev = rfbdev;

	drm_fb_helper_prepare(rdev->ddev, &rfbdev->helper,
			      &radeon_fb_helper_funcs);

	ret = drm_fb_helper_init(rdev->ddev, &rfbdev->helper,
				 rdev->num_crtc,
				 RADEONFB_CONN_LIMIT);
	if (ret)
		goto free;

	ret = drm_fb_helper_single_add_all_connectors(&rfbdev->helper);
	if (ret)
		goto fini;


	drm_helper_disable_unused_functions(rdev->ddev);

	ret = drm_fb_helper_initial_config(&rfbdev->helper, bpp_sel);
	if (ret)
		goto fini;

	return 0;

fini:
	drm_fb_helper_fini(&rfbdev->helper);
free:
	kfree(rfbdev);
	return ret;
}
