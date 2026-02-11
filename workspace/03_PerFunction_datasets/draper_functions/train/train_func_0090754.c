psb_framebuffer_create
			(struct drm_device *dev,
			 struct drm_mode_fb_cmd2 *mode_cmd,
			 struct gtt_range *gt)
{
	struct psb_framebuffer *fb;
	int ret;

	fb = kzalloc(sizeof(*fb), GFP_KERNEL);
	if (!fb)
		return ERR_PTR(-ENOMEM);

	ret = psb_framebuffer_init(dev, fb, mode_cmd, gt);
	if (ret) {
		kfree(fb);
		return ERR_PTR(ret);
	}
	return &fb->base;
}
