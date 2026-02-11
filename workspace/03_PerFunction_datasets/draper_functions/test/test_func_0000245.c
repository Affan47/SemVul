wait_for_fences(struct drm_device *dev,
			    struct drm_atomic_state *state)
{
	struct drm_plane *plane;
	struct drm_plane_state *plane_state;
	int i;

	for_each_plane_in_state(state, plane, plane_state, i) {
		if (!plane->state->fence)
			continue;

		WARN_ON(!plane->state->fb);

		fence_wait(plane->state->fence, false);
		fence_put(plane->state->fence);
		plane->state->fence = NULL;
	}
}
