qxl_framebuffer_surface_dirty(struct drm_framebuffer *fb,
					 struct drm_file *file_priv,
					 unsigned flags, unsigned color,
					 struct drm_clip_rect *clips,
					 unsigned num_clips)
{

	struct qxl_framebuffer *qxl_fb = to_qxl_framebuffer(fb);
	struct qxl_device *qdev = qxl_fb->base.dev->dev_private;
	struct drm_clip_rect norect;
	struct qxl_bo *qobj;
	int inc = 1;

	drm_modeset_lock_all(fb->dev);

	qobj = gem_to_qxl_bo(qxl_fb->obj);

	if (!qobj->is_primary) {
		drm_modeset_unlock_all(fb->dev);
		return 0;
	}

	if (!num_clips) {
		num_clips = 1;
		clips = &norect;
		norect.x1 = norect.y1 = 0;
		norect.x2 = fb->width;
		norect.y2 = fb->height;
	} else if (flags & DRM_MODE_FB_DIRTY_ANNOTATE_COPY) {
		num_clips /= 2;
		inc = 2;
	}

	qxl_draw_dirty_fb(qdev, qxl_fb, qobj, flags, color,
			  clips, num_clips, inc);

	drm_modeset_unlock_all(fb->dev);

	return 0;
}
