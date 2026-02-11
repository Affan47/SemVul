drm_atomic_helper_cleanup_planes(struct drm_device *dev,
				      struct drm_atomic_state *old_state)
{
	struct drm_plane *plane;
	struct drm_plane_state *plane_state;
	int i;

	for_each_plane_in_state(old_state, plane, plane_state, i) {
		const struct drm_plane_helper_funcs *funcs;

		funcs = plane->helper_private;

		if (funcs->cleanup_fb)
			funcs->cleanup_fb(plane, plane_state);
	}
}
