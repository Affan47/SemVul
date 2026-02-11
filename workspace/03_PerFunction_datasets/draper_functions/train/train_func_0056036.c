drm_plane_helper_update(struct drm_plane *plane, struct drm_crtc *crtc,
			    struct drm_framebuffer *fb,
			    int crtc_x, int crtc_y,
			    unsigned int crtc_w, unsigned int crtc_h,
			    uint32_t src_x, uint32_t src_y,
			    uint32_t src_w, uint32_t src_h)
{
	struct drm_plane_state *plane_state;

	if (plane->funcs->atomic_duplicate_state)
		plane_state = plane->funcs->atomic_duplicate_state(plane);
	else {
		if (!plane->state)
			drm_atomic_helper_plane_reset(plane);

		plane_state = drm_atomic_helper_plane_duplicate_state(plane);
	}
	if (!plane_state)
		return -ENOMEM;
	plane_state->plane = plane;

	plane_state->crtc = crtc;
	drm_atomic_set_fb_for_plane(plane_state, fb);
	plane_state->crtc_x = crtc_x;
	plane_state->crtc_y = crtc_y;
	plane_state->crtc_h = crtc_h;
	plane_state->crtc_w = crtc_w;
	plane_state->src_x = src_x;
	plane_state->src_y = src_y;
	plane_state->src_h = src_h;
	plane_state->src_w = src_w;

	return drm_plane_helper_commit(plane, plane_state, plane->fb);
}
