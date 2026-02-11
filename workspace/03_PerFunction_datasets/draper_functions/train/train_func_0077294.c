drm_intel_gem_bo_unmap(drm_intel_bo *bo)
{
	drm_intel_bufmgr_gem *bufmgr_gem = (drm_intel_bufmgr_gem *) bo->bufmgr;
	drm_intel_bo_gem *bo_gem = (drm_intel_bo_gem *) bo;
	int ret = 0;

	if (bo == NULL)
		return 0;

	pthread_mutex_lock(&bufmgr_gem->lock);

	if (bo_gem->map_count <= 0) {
		DBG("attempted to unmap an unmapped bo\n");
		pthread_mutex_unlock(&bufmgr_gem->lock);


		return 0;
	}

	if (bo_gem->mapped_cpu_write) {
		struct drm_i915_gem_sw_finish sw_finish;


		VG_CLEAR(sw_finish);
		sw_finish.handle = bo_gem->gem_handle;
		ret = drmIoctl(bufmgr_gem->fd,
			       DRM_IOCTL_I915_GEM_SW_FINISH,
			       &sw_finish);
		ret = ret == -1 ? -errno : 0;

		bo_gem->mapped_cpu_write = false;
	}


	if (--bo_gem->map_count == 0) {
		drm_intel_gem_bo_close_vma(bufmgr_gem, bo_gem);
		drm_intel_gem_bo_mark_mmaps_incoherent(bo);
		bo->virtual = NULL;
	}
	pthread_mutex_unlock(&bufmgr_gem->lock);

	return ret;
}
