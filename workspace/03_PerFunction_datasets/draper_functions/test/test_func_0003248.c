__drm_atomic_helper_plane_duplicate_state(struct drm_plane *plane,
					       struct drm_plane_state *state)
{
	memcpy(state, plane->state, sizeof(*state));

	if (state->fb)
		drm_framebuffer_reference(state->fb);
}
