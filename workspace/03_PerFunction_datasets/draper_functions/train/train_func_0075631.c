i915_gem_obj_total_ggtt_size(struct drm_i915_gem_object *obj)
{
	u64 size = 0;
	struct i915_vma *vma;

	list_for_each_entry(vma, &obj->vma_list, obj_link) {
		if (vma->is_ggtt && drm_mm_node_allocated(&vma->node))
			size += vma->node.size;
	}

	return size;
}
