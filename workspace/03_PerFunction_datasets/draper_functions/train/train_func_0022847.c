qxl_user_framebuffer_create(struct drm_device *dev,
			    struct drm_file *file_priv,
			    struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_gem_object *obj;
	struct qxl_framebuffer *qxl_fb;
	int ret;

	obj = drm_gem_object_lookup(dev, file_priv, mode_cmd->handles[0]);

	qxl_fb = kzalloc(sizeof(*qxl_fb), GFP_KERNEL);
	if (qxl_fb == NULL)
		return NULL;

	ret = qxl_framebuffer_init(dev, qxl_fb, mode_cmd, obj);
	if (ret) {
		kfree(qxl_fb);
		drm_gem_object_unreference_unlocked(obj);
		return NULL;
	}

	return &qxl_fb->base;
}
