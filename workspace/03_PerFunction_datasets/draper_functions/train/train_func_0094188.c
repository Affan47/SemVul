drm_intel_gem_bo_close_vma(drm_intel_bufmgr_gem *bufmgr_gem,
				       drm_intel_bo_gem *bo_gem)
{
	bufmgr_gem->vma_open--;
	DRMLISTADDTAIL(&bo_gem->vma_list, &bufmgr_gem->vma_cache);
	if (bo_gem->mem_virtual)
		bufmgr_gem->vma_count++;
	if (bo_gem->gtt_virtual)
		bufmgr_gem->vma_count++;
	drm_intel_gem_bo_purge_vma_cache(bufmgr_gem);
}
