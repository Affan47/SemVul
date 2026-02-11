i915_gem_find_active_request(struct intel_engine_cs *ring)
{
	struct drm_i915_gem_request *request;

	list_for_each_entry(request, &ring->request_list, list) {
		if (i915_gem_request_completed(request, false))
			continue;

		return request;
	}

	return NULL;
}
