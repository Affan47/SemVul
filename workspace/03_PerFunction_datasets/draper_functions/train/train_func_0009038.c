drm_intel_gem_bo_map_unsynchronized(drm_intel_bo *bo)
{
	drm_intel_bufmgr_gem *bufmgr_gem = (drm_intel_bufmgr_gem *) bo->bufmgr;
#ifdef HAVE_VALGRIND
	drm_intel_bo_gem *bo_gem = (drm_intel_bo_gem *) bo;
#endif
	int ret;


	if (!bufmgr_gem->has_llc)
		return drm_intel_gem_bo_map_gtt(bo);

	pthread_mutex_lock(&bufmgr_gem->lock);

	ret = map_gtt(bo);
	if (ret == 0) {
		drm_intel_gem_bo_mark_mmaps_incoherent(bo);
		VG(VALGRIND_MAKE_MEM_DEFINED(bo_gem->gtt_virtual, bo->size));
	}

	pthread_mutex_unlock(&bufmgr_gem->lock);

	return ret;
}
