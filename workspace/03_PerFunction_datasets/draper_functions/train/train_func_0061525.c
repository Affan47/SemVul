copy_batch(struct drm_i915_gem_object *dest_obj,
		       struct drm_i915_gem_object *src_obj,
		       u32 batch_start_offset,
		       u32 batch_len)
{
	int needs_clflush = 0;
	void *src_base, *src;
	void *dst = NULL;
	int ret;

	if (batch_len > dest_obj->base.size ||
	    batch_len + batch_start_offset > src_obj->base.size)
		return ERR_PTR(-E2BIG);

	if (WARN_ON(dest_obj->pages_pin_count == 0))
		return ERR_PTR(-ENODEV);

	ret = i915_gem_obj_prepare_shmem_read(src_obj, &needs_clflush);
	if (ret) {
		DRM_DEBUG_DRIVER("CMD: failed to prepare shadow batch\n");
		return ERR_PTR(ret);
	}

	src_base = vmap_batch(src_obj, batch_start_offset, batch_len);
	if (!src_base) {
		DRM_DEBUG_DRIVER("CMD: Failed to vmap batch\n");
		ret = -ENOMEM;
		goto unpin_src;
	}

	ret = i915_gem_object_set_to_cpu_domain(dest_obj, true);
	if (ret) {
		DRM_DEBUG_DRIVER("CMD: Failed to set shadow batch to CPU\n");
		goto unmap_src;
	}

	dst = vmap_batch(dest_obj, 0, batch_len);
	if (!dst) {
		DRM_DEBUG_DRIVER("CMD: Failed to vmap shadow batch\n");
		ret = -ENOMEM;
		goto unmap_src;
	}

	src = src_base + offset_in_page(batch_start_offset);
	if (needs_clflush)
		drm_clflush_virt_range(src, batch_len);

	memcpy(dst, src, batch_len);

unmap_src:
	vunmap(src_base);
unpin_src:
	i915_gem_object_unpin_pages(src_obj);

	return ret ? ERR_PTR(ret) : dst;
}
