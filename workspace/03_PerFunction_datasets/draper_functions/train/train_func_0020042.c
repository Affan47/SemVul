i915_gem_record_active_context(struct intel_engine_cs *ring,
					   struct drm_i915_error_state *error,
					   struct drm_i915_error_ring *ering)
{
	struct drm_i915_private *dev_priv = ring->dev->dev_private;
	struct drm_i915_gem_object *obj;


	if (ring->id != RCS || !error->ccid)
		return;

	list_for_each_entry(obj, &dev_priv->mm.bound_list, global_list) {
		if (!i915_gem_obj_ggtt_bound(obj))
			continue;

		if ((error->ccid & PAGE_MASK) == i915_gem_obj_ggtt_offset(obj)) {
			ering->ctx = i915_error_ggtt_object_create(dev_priv, obj);
			break;
		}
	}
}
