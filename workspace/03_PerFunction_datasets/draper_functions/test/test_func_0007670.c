drm_intel_gem_bo_set_tiling_internal(drm_intel_bo *bo,
				     uint32_t tiling_mode,
				     uint32_t stride)
{
	drm_intel_bufmgr_gem *bufmgr_gem = (drm_intel_bufmgr_gem *) bo->bufmgr;
	drm_intel_bo_gem *bo_gem = (drm_intel_bo_gem *) bo;
	struct drm_i915_gem_set_tiling set_tiling;
	int ret;

	if (bo_gem->global_name == 0 &&
	    tiling_mode == bo_gem->tiling_mode &&
	    stride == bo_gem->stride)
		return 0;

	memset(&set_tiling, 0, sizeof(set_tiling));
	do {


		set_tiling.handle = bo_gem->gem_handle;
		set_tiling.tiling_mode = tiling_mode;
		set_tiling.stride = stride;

		ret = ioctl(bufmgr_gem->fd,
			    DRM_IOCTL_I915_GEM_SET_TILING,
			    &set_tiling);
	} while (ret == -1 && (errno == EINTR || errno == EAGAIN));
	if (ret == -1)
		return -errno;

	bo_gem->tiling_mode = set_tiling.tiling_mode;
	bo_gem->swizzle_mode = set_tiling.swizzle_mode;
	bo_gem->stride = set_tiling.stride;
	return 0;
}
