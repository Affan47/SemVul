i915_gem_object_flush_cpu_write_domain(struct drm_i915_gem_object *obj)
{
	uint32_t old_write_domain;

	if (obj->base.write_domain != I915_GEM_DOMAIN_CPU)
		return;

	if (i915_gem_clflush_object(obj, obj->pin_display))
		i915_gem_chipset_flush(obj->base.dev);

	old_write_domain = obj->base.write_domain;
	obj->base.write_domain = 0;

	intel_fb_obj_flush(obj, false, ORIGIN_CPU);

	trace_i915_gem_object_change_domain(obj,
					    obj->base.read_domains,
					    old_write_domain);
}
