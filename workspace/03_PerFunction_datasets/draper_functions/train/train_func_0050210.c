vmw_user_dmabuf_synccpu_grab(struct vmw_user_dma_buffer *user_bo,
					struct ttm_object_file *tfile,
					uint32_t flags)
{
	struct ttm_buffer_object *bo = &user_bo->dma.base;
	bool existed;
	int ret;

	if (flags & drm_vmw_synccpu_allow_cs) {
		bool nonblock = !!(flags & drm_vmw_synccpu_dontblock);
		long lret;

		if (nonblock)
			return reservation_object_test_signaled_rcu(bo->resv, true) ? 0 : -EBUSY;

		lret = reservation_object_wait_timeout_rcu(bo->resv, true, true, MAX_SCHEDULE_TIMEOUT);
		if (!lret)
			return -EBUSY;
		else if (lret < 0)
			return lret;
		return 0;
	}

	ret = ttm_bo_synccpu_write_grab
		(bo, !!(flags & drm_vmw_synccpu_dontblock));
	if (unlikely(ret != 0))
		return ret;

	ret = ttm_ref_object_add(tfile, &user_bo->prime.base,
				 TTM_REF_SYNCCPU_WRITE, &existed, false);
	if (ret != 0 || existed)
		ttm_bo_synccpu_write_release(&user_bo->dma.base);

	return ret;
}
