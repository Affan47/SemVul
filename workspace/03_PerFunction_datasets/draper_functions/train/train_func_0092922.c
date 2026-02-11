drm_helper_crtc_mode_set_base(struct drm_crtc *crtc, int x, int y,
				  struct drm_framebuffer *old_fb)
{
	struct drm_plane_state *plane_state;
	struct drm_plane *plane = crtc->primary;

	if (plane->funcs->atomic_duplicate_state)
		plane_state = plane->funcs->atomic_duplicate_state(plane);
	else if (plane->state)
		plane_state = drm_atomic_helper_plane_duplicate_state(plane);
	else
		plane_state = kzalloc(sizeof(*plane_state), GFP_KERNEL);
	if (!plane_state)
		return -ENOMEM;
	plane_state->plane = plane;

	plane_state->crtc = crtc;
	drm_atomic_set_fb_for_plane(plane_state, crtc->primary->fb);
	plane_state->crtc_x = 0;
	plane_state->crtc_y = 0;
	plane_state->crtc_h = crtc->mode.vdisplay;
	plane_state->crtc_w = crtc->mode.hdisplay;
	plane_state->src_x = x << 16;
	plane_state->src_y = y << 16;
	plane_state->src_h = crtc->mode.vdisplay << 16;
	plane_state->src_w = crtc->mode.hdisplay << 16;

	return drm_plane_helper_commit(plane, plane_state, old_fb);
}
