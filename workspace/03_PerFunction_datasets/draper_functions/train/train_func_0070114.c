per_file_stats(int id, void *ptr, void *data)
{
	struct drm_i915_gem_object *obj = ptr;
	struct file_stats *stats = data;
	struct i915_vma *vma;

	stats->count++;
	stats->total += obj->base.size;

	if (obj->base.name || obj->base.dma_buf)
		stats->shared += obj->base.size;

	if (USES_FULL_PPGTT(obj->base.dev)) {
		list_for_each_entry(vma, &obj->vma_list, vma_link) {
			struct i915_hw_ppgtt *ppgtt;

			if (!drm_mm_node_allocated(&vma->node))
				continue;

			if (i915_is_ggtt(vma->vm)) {
				stats->global += obj->base.size;
				continue;
			}

			ppgtt = container_of(vma->vm, struct i915_hw_ppgtt, base);
			if (ppgtt->file_priv != stats->file_priv)
				continue;

			if (obj->active)
				stats->active += obj->base.size;
			else
				stats->inactive += obj->base.size;

			return 0;
		}
	} else {
		if (i915_gem_obj_ggtt_bound(obj)) {
			stats->global += obj->base.size;
			if (obj->active)
				stats->active += obj->base.size;
			else
				stats->inactive += obj->base.size;
			return 0;
		}
	}

	if (!list_empty(&obj->global_list))
		stats->unbound += obj->base.size;

	return 0;
}
