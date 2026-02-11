intel_plane_duplicate_state(struct drm_plane *plane)
{
	struct drm_plane_state *state;
	struct intel_plane_state *intel_state;

	intel_state = kmemdup(plane->state, sizeof(*intel_state), GFP_KERNEL);

	if (!intel_state)
		return NULL;

	state = &intel_state->base;

	__drm_atomic_helper_plane_duplicate_state(plane, state);

	return state;
}
