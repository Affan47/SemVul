udlfb_create(struct drm_fb_helper *helper,
			struct drm_fb_helper_surface_size *sizes)
{
	struct udl_fbdev *ufbdev =
		container_of(helper, struct udl_fbdev, helper);
	struct drm_device *dev = ufbdev->helper.dev;
	struct fb_info *info;
	struct drm_framebuffer *fb;
	struct drm_mode_fb_cmd2 mode_cmd;
	struct udl_gem_object *obj;
	uint32_t size;
	int ret = 0;

	if (sizes->surface_bpp == 24)
		sizes->surface_bpp = 32;

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;
	mode_cmd.pitches[0] = mode_cmd.width * ((sizes->surface_bpp + 7) / 8);

	mode_cmd.pixel_format = drm_mode_legacy_fb_format(sizes->surface_bpp,
							  sizes->surface_depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;
	size = ALIGN(size, PAGE_SIZE);

	obj = udl_gem_alloc_object(dev, size);
	if (!obj)
		goto out;

	ret = udl_gem_vmap(obj);
	if (ret) {
		DRM_ERROR("failed to vmap fb\n");
		goto out_gfree;
	}

	info = drm_fb_helper_alloc_fbi(helper);
	if (IS_ERR(info)) {
		ret = PTR_ERR(info);
		goto out_gfree;
	}
	info->par = ufbdev;

	ret = udl_framebuffer_init(dev, &ufbdev->ufb, &mode_cmd, obj);
	if (ret)
		goto out_destroy_fbi;

	fb = &ufbdev->ufb.base;

	ufbdev->helper.fb = fb;

	strcpy(info->fix.id, "udldrmfb");

	info->screen_base = ufbdev->ufb.obj->vmapping;
	info->fix.smem_len = size;
	info->fix.smem_start = (unsigned long)ufbdev->ufb.obj->vmapping;

	info->flags = FBINFO_DEFAULT | FBINFO_CAN_FORCE_OUTPUT;
	info->fbops = &udlfb_ops;
	drm_fb_helper_fill_fix(info, fb->pitches[0], fb->depth);
	drm_fb_helper_fill_var(info, &ufbdev->helper, sizes->fb_width, sizes->fb_height);

	DRM_DEBUG_KMS("allocated %dx%d vmal %p\n",
		      fb->width, fb->height,
		      ufbdev->ufb.obj->vmapping);

	return ret;
out_destroy_fbi:
	drm_fb_helper_release_fbi(helper);
out_gfree:
	drm_gem_object_unreference_unlocked(&ufbdev->ufb.obj->base);
out:
	return ret;
}
