do_exec2(drm_intel_bo *bo, int used, drm_intel_context *ctx,
	 drm_clip_rect_t *cliprects, int num_cliprects, int DR4,
	 unsigned int flags)
{
	drm_intel_bufmgr_gem *bufmgr_gem = (drm_intel_bufmgr_gem *)bo->bufmgr;
	struct drm_i915_gem_execbuffer2 execbuf;
	int ret = 0;
	int i;

	if (to_bo_gem(bo)->has_error)
		return -ENOMEM;

	switch (flags & 0x7) {
	default:
		return -EINVAL;
	case I915_EXEC_BLT:
		if (!bufmgr_gem->has_blt)
			return -EINVAL;
		break;
	case I915_EXEC_BSD:
		if (!bufmgr_gem->has_bsd)
			return -EINVAL;
		break;
	case I915_EXEC_VEBOX:
		if (!bufmgr_gem->has_vebox)
			return -EINVAL;
		break;
	case I915_EXEC_RENDER:
	case I915_EXEC_DEFAULT:
		break;
	}

	pthread_mutex_lock(&bufmgr_gem->lock);

	drm_intel_gem_bo_process_reloc2(bo);


	drm_intel_add_validate_buffer2(bo, 0);

	memclear(execbuf);
	execbuf.buffers_ptr = (uintptr_t)bufmgr_gem->exec2_objects;
	execbuf.buffer_count = bufmgr_gem->exec_count;
	execbuf.batch_start_offset = 0;
	execbuf.batch_len = used;
	execbuf.cliprects_ptr = (uintptr_t)cliprects;
	execbuf.num_cliprects = num_cliprects;
	execbuf.DR1 = 0;
	execbuf.DR4 = DR4;
	execbuf.flags = flags;
	if (ctx == NULL)
		i915_execbuffer2_set_context_id(execbuf, 0);
	else
		i915_execbuffer2_set_context_id(execbuf, ctx->ctx_id);
	execbuf.rsvd2 = 0;

	if (bufmgr_gem->no_exec)
		goto skip_execution;

	ret = drmIoctl(bufmgr_gem->fd,
		       DRM_IOCTL_I915_GEM_EXECBUFFER2,
		       &execbuf);
	if (ret != 0) {
		ret = -errno;
		if (ret == -ENOSPC) {
			DBG("Execbuffer fails to pin. "
			    "Estimate: %u. Actual: %u. Available: %u\n",
			    drm_intel_gem_estimate_batch_space(bufmgr_gem->exec_bos,
							       bufmgr_gem->exec_count),
			    drm_intel_gem_compute_batch_space(bufmgr_gem->exec_bos,
							      bufmgr_gem->exec_count),
			    (unsigned int) bufmgr_gem->gtt_size);
		}
	}
	drm_intel_update_buffer_offsets2(bufmgr_gem);

skip_execution:
	if (bufmgr_gem->bufmgr.debug)
		drm_intel_gem_dump_validation_list(bufmgr_gem);

	for (i = 0; i < bufmgr_gem->exec_count; i++) {
		drm_intel_bo_gem *bo_gem = to_bo_gem(bufmgr_gem->exec_bos[i]);

		bo_gem->idle = false;


		bo_gem->validate_index = -1;
		bufmgr_gem->exec_bos[i] = NULL;
	}
	bufmgr_gem->exec_count = 0;
	pthread_mutex_unlock(&bufmgr_gem->lock);

	return ret;
}
