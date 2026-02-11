drm_intel_gem_bo_exec(drm_intel_bo *bo, int used,
		      drm_clip_rect_t * cliprects, int num_cliprects, int DR4)
{
	drm_intel_bufmgr_gem *bufmgr_gem = (drm_intel_bufmgr_gem *) bo->bufmgr;
	drm_intel_bo_gem *bo_gem = (drm_intel_bo_gem *) bo;
	struct drm_i915_gem_execbuffer execbuf;
	int ret, i;

	if (bo_gem->has_error)
		return -ENOMEM;

	pthread_mutex_lock(&bufmgr_gem->lock);

	drm_intel_gem_bo_process_reloc(bo);


	drm_intel_add_validate_buffer(bo);

	VG_CLEAR(execbuf);
	execbuf.buffers_ptr = (uintptr_t) bufmgr_gem->exec_objects;
	execbuf.buffer_count = bufmgr_gem->exec_count;
	execbuf.batch_start_offset = 0;
	execbuf.batch_len = used;
	execbuf.cliprects_ptr = (uintptr_t) cliprects;
	execbuf.num_cliprects = num_cliprects;
	execbuf.DR1 = 0;
	execbuf.DR4 = DR4;

	ret = drmIoctl(bufmgr_gem->fd,
		       DRM_IOCTL_I915_GEM_EXECBUFFER,
		       &execbuf);
	if (ret != 0) {
		ret = -errno;
		if (errno == ENOSPC) {
			DBG("Execbuffer fails to pin. "
			    "Estimate: %u. Actual: %u. Available: %u\n",
			    drm_intel_gem_estimate_batch_space(bufmgr_gem->exec_bos,
							       bufmgr_gem->
							       exec_count),
			    drm_intel_gem_compute_batch_space(bufmgr_gem->exec_bos,
							      bufmgr_gem->
							      exec_count),
			    (unsigned int)bufmgr_gem->gtt_size);
		}
	}
	drm_intel_update_buffer_offsets(bufmgr_gem);

	if (bufmgr_gem->bufmgr.debug)
		drm_intel_gem_dump_validation_list(bufmgr_gem);

	for (i = 0; i < bufmgr_gem->exec_count; i++) {
		drm_intel_bo *bo = bufmgr_gem->exec_bos[i];
		drm_intel_bo_gem *bo_gem = (drm_intel_bo_gem *) bo;

		bo_gem->idle = false;


		bo_gem->validate_index = -1;
		bufmgr_gem->exec_bos[i] = NULL;
	}
	bufmgr_gem->exec_count = 0;
	pthread_mutex_unlock(&bufmgr_gem->lock);

	return ret;
}
