_drm_intel_gem_bo_references(drm_intel_bo *bo, drm_intel_bo *target_bo)
{
	drm_intel_bo_gem *bo_gem = (drm_intel_bo_gem *) bo;
	int i;

	for (i = 0; i < bo_gem->reloc_count; i++) {
		if (bo_gem->reloc_target_info[i].bo == target_bo)
			return 1;
		if (bo == bo_gem->reloc_target_info[i].bo)
			continue;
		if (_drm_intel_gem_bo_references(bo_gem->reloc_target_info[i].bo,
						target_bo))
			return 1;
	}

	return 0;
}
