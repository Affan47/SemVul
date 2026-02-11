drm_atomic_clean_old_fb(struct drm_device *dev,
			     unsigned plane_mask,
			     int ret)
{
	struct drm_plane *plane;


	drm_for_each_plane_mask(plane, dev, plane_mask) {
		if (ret == 0) {
			struct drm_framebuffer *new_fb = plane->state->fb;
			if (new_fb)
				drm_framebuffer_reference(new_fb);
			plane->fb = new_fb;
			plane->crtc = plane->state->crtc;

			if (plane->old_fb)
				drm_framebuffer_unreference(plane->old_fb);
		}
		plane->old_fb = NULL;
	}
}
