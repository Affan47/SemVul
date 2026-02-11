skl_compute_wm_pipe_parameters(struct drm_crtc *crtc,
					   struct skl_pipe_wm_parameters *p)
{
	struct drm_device *dev = crtc->dev;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	enum pipe pipe = intel_crtc->pipe;
	struct drm_plane *plane;
	struct drm_framebuffer *fb;
	int i = 1;

	p->active = intel_crtc->active;
	if (p->active) {
		p->pipe_htotal = intel_crtc->config->base.adjusted_mode.crtc_htotal;
		p->pixel_rate = skl_pipe_pixel_rate(intel_crtc->config);

		fb = crtc->primary->state->fb;

		if (fb) {
			p->plane[0].enabled = true;
			p->plane[0].bytes_per_pixel = fb->pixel_format == DRM_FORMAT_NV12 ?
				drm_format_plane_cpp(fb->pixel_format, 1) :
				drm_format_plane_cpp(fb->pixel_format, 0);
			p->plane[0].y_bytes_per_pixel = fb->pixel_format == DRM_FORMAT_NV12 ?
				drm_format_plane_cpp(fb->pixel_format, 0) : 0;
			p->plane[0].tiling = fb->modifier[0];
		} else {
			p->plane[0].enabled = false;
			p->plane[0].bytes_per_pixel = 0;
			p->plane[0].y_bytes_per_pixel = 0;
			p->plane[0].tiling = DRM_FORMAT_MOD_NONE;
		}
		p->plane[0].horiz_pixels = intel_crtc->config->pipe_src_w;
		p->plane[0].vert_pixels = intel_crtc->config->pipe_src_h;
		p->plane[0].rotation = crtc->primary->state->rotation;

		fb = crtc->cursor->state->fb;
		p->plane[PLANE_CURSOR].y_bytes_per_pixel = 0;
		if (fb) {
			p->plane[PLANE_CURSOR].enabled = true;
			p->plane[PLANE_CURSOR].bytes_per_pixel = fb->bits_per_pixel / 8;
			p->plane[PLANE_CURSOR].horiz_pixels = crtc->cursor->state->crtc_w;
			p->plane[PLANE_CURSOR].vert_pixels = crtc->cursor->state->crtc_h;
		} else {
			p->plane[PLANE_CURSOR].enabled = false;
			p->plane[PLANE_CURSOR].bytes_per_pixel = 0;
			p->plane[PLANE_CURSOR].horiz_pixels = 64;
			p->plane[PLANE_CURSOR].vert_pixels = 64;
		}
	}

	list_for_each_entry(plane, &dev->mode_config.plane_list, head) {
		struct intel_plane *intel_plane = to_intel_plane(plane);

		if (intel_plane->pipe == pipe &&
			plane->type == DRM_PLANE_TYPE_OVERLAY)
			p->plane[i++] = intel_plane->wm;
	}
}
