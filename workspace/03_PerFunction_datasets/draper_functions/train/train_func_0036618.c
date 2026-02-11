mgag200fb_create(struct drm_fb_helper *helper,
			   struct drm_fb_helper_surface_size *sizes)
{
	struct mga_fbdev *mfbdev =
		container_of(helper, struct mga_fbdev, helper);
	struct drm_device *dev = mfbdev->helper.dev;
	struct drm_mode_fb_cmd2 mode_cmd;
	struct mga_device *mdev = dev->dev_private;
	struct fb_info *info;
	struct drm_framebuffer *fb;
	struct drm_gem_object *gobj = NULL;
	int ret;
	void *sysram;
	int size;

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;
	mode_cmd.pitches[0] = mode_cmd.width * ((sizes->surface_bpp + 7) / 8);

	mode_cmd.pixel_format = drm_mode_legacy_fb_format(sizes->surface_bpp,
							  sizes->surface_depth);
	size = mode_cmd.pitches[0] * mode_cmd.height;

	ret = mgag200fb_create_object(mfbdev, &mode_cmd, &gobj);
	if (ret) {
		DRM_ERROR("failed to create fbcon backing object %d\n", ret);
		return ret;
	}

	sysram = vmalloc(size);
	if (!sysram)
		goto err_sysram;

	info = drm_fb_helper_alloc_fbi(helper);
	if (IS_ERR(info)) {
		ret = PTR_ERR(info);
		goto err_alloc_fbi;
	}

	info->par = mfbdev;

	ret = mgag200_framebuffer_init(dev, &mfbdev->mfb, &mode_cmd, gobj);
	if (ret)
		goto err_framebuffer_init;

	mfbdev->sysram = sysram;
	mfbdev->size = size;

	fb = &mfbdev->mfb.base;


	mfbdev->helper.fb = fb;

	strcpy(info->fix.id, "mgadrmfb");

	info->flags = FBINFO_DEFAULT | FBINFO_CAN_FORCE_OUTPUT;
	info->fbops = &mgag200fb_ops;


	info->apertures->ranges[0].base = mdev->dev->mode_config.fb_base;
	info->apertures->ranges[0].size = mdev->mc.vram_size;

	drm_fb_helper_fill_fix(info, fb->pitches[0], fb->depth);
	drm_fb_helper_fill_var(info, &mfbdev->helper, sizes->fb_width,
			       sizes->fb_height);

	info->screen_base = sysram;
	info->screen_size = size;
	info->pixmap.flags = FB_PIXMAP_SYSTEM;

	DRM_DEBUG_KMS("allocated %dx%d\n",
		      fb->width, fb->height);

	return 0;

err_framebuffer_init:
	drm_fb_helper_release_fbi(helper);
err_alloc_fbi:
	vfree(sysram);
err_sysram:
	drm_gem_object_unreference_unlocked(gobj);

	return ret;
}
