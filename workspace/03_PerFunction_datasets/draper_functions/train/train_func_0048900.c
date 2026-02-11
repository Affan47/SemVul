aub_write_bo_data(drm_intel_bo *bo, uint32_t offset, uint32_t size)
{
	drm_intel_bufmgr_gem *bufmgr_gem = (drm_intel_bufmgr_gem *) bo->bufmgr;
	drm_intel_bo_gem *bo_gem = (drm_intel_bo_gem *) bo;
	uint32_t *data;
	unsigned int i;

	data = malloc(bo->size);
	drm_intel_bo_get_subdata(bo, offset, size, data);


	if (!bo_gem->reloc_count) {
		aub_out_data(bufmgr_gem, data, size);
		free(data);
		return;
	}


	for (i = 0; i < size / 4; i++) {
		int r;
		for (r = 0; r < bo_gem->reloc_count; r++) {
			struct drm_i915_gem_relocation_entry *reloc;
			drm_intel_reloc_target *info;

			reloc = &bo_gem->relocs[r];
			info = &bo_gem->reloc_target_info[r];

			if (reloc->offset == offset + i * 4) {
				drm_intel_bo_gem *target_gem;
				uint32_t val;

				target_gem = (drm_intel_bo_gem *)info->bo;

				val = reloc->delta;
				val += target_gem->aub_offset;

				aub_out(bufmgr_gem, val);
				data[i] = val;
				break;
			}
		}
		if (r == bo_gem->reloc_count) {

			aub_out(bufmgr_gem, data[i]);
		}
	}

	free(data);
}
