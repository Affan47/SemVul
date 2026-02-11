gen8_init_rcs_context(struct drm_i915_gem_request *req)
{
	int ret;

	ret = intel_logical_ring_workarounds_emit(req);
	if (ret)
		return ret;

	ret = intel_rcs_context_init_mocs(req);


	if (ret)
		DRM_ERROR("MOCS failed to program: expect performance issues.\n");

	return intel_lr_context_render_state_init(req);
}
