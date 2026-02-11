i915_gem_execbuffer_reserve_vma(struct i915_vma *vma,
				struct intel_engine_cs *ring,
				bool *need_reloc)
{
	struct drm_i915_gem_object *obj = vma->obj;
	struct drm_i915_gem_exec_object2 *entry = vma->exec_entry;
	uint64_t flags;
	int ret;

	flags = PIN_USER;
	if (entry->flags & EXEC_OBJECT_NEEDS_GTT)
		flags |= PIN_GLOBAL;

	if (!drm_mm_node_allocated(&vma->node)) {


		if ((entry->flags & EXEC_OBJECT_SUPPORTS_48B_ADDRESS) == 0)
			flags |= PIN_ZONE_4G;
		if (entry->flags & __EXEC_OBJECT_NEEDS_MAP)
			flags |= PIN_GLOBAL | PIN_MAPPABLE;
		if (entry->flags & __EXEC_OBJECT_NEEDS_BIAS)
			flags |= BATCH_OFFSET_BIAS | PIN_OFFSET_BIAS;
		if ((flags & PIN_MAPPABLE) == 0)
			flags |= PIN_HIGH;
	}

	ret = i915_gem_object_pin(obj, vma->vm, entry->alignment, flags);
	if ((ret == -ENOSPC  || ret == -E2BIG) &&
	    only_mappable_for_reloc(entry->flags))
		ret = i915_gem_object_pin(obj, vma->vm,
					  entry->alignment,
					  flags & ~PIN_MAPPABLE);
	if (ret)
		return ret;

	entry->flags |= __EXEC_OBJECT_HAS_PIN;

	if (entry->flags & EXEC_OBJECT_NEEDS_FENCE) {
		ret = i915_gem_object_get_fence(obj);
		if (ret)
			return ret;

		if (i915_gem_object_pin_fence(obj))
			entry->flags |= __EXEC_OBJECT_HAS_FENCE;
	}

	if (entry->offset != vma->node.start) {
		entry->offset = vma->node.start;
		*need_reloc = true;
	}

	if (entry->flags & EXEC_OBJECT_WRITE) {
		obj->base.pending_read_domains = I915_GEM_DOMAIN_RENDER;
		obj->base.pending_write_domain = I915_GEM_DOMAIN_RENDER;
	}

	return 0;
}
