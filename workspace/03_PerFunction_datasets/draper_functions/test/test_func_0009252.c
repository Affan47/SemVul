ttm_bo_cleanup_refs_or_queue(struct ttm_buffer_object *bo)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_bo_global *glob = bo->glob;
	int put_count;
	int ret;

	spin_lock(&glob->lru_lock);
	ret = __ttm_bo_reserve(bo, false, true, false, NULL);

	if (!ret) {
		if (!ttm_bo_wait(bo, false, false, true)) {
			put_count = ttm_bo_del_from_lru(bo);

			spin_unlock(&glob->lru_lock);
			ttm_bo_cleanup_memtype_use(bo);

			ttm_bo_list_ref_sub(bo, put_count, true);

			return;
		} else
			ttm_bo_flush_all_fences(bo);


		if (bo->mem.placement & TTM_PL_FLAG_NO_EVICT) {
			bo->mem.placement &= ~TTM_PL_FLAG_NO_EVICT;
			ttm_bo_add_to_lru(bo);
		}

		__ttm_bo_unreserve(bo);
	}

	kref_get(&bo->list_kref);
	list_add_tail(&bo->ddestroy, &bdev->ddestroy);
	spin_unlock(&glob->lru_lock);

	schedule_delayed_work(&bdev->wq,
			      ((HZ / 100) < 1) ? 1 : HZ / 100);
}
