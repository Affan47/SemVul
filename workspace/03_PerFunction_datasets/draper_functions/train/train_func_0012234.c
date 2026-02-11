ttm_bo_device_release(struct ttm_bo_device *bdev)
{
	int ret = 0;
	unsigned i = TTM_NUM_MEM_TYPES;
	struct ttm_mem_type_manager *man;
	struct ttm_bo_global *glob = bdev->glob;

	while (i--) {
		man = &bdev->man[i];
		if (man->has_type) {
			man->use_type = false;
			if ((i != TTM_PL_SYSTEM) && ttm_bo_clean_mm(bdev, i)) {
				ret = -EBUSY;
				pr_err("DRM memory manager type %d is not clean\n",
				       i);
			}
			man->has_type = false;
		}
	}

	mutex_lock(&glob->device_list_mutex);
	list_del(&bdev->device_list);
	mutex_unlock(&glob->device_list_mutex);

	cancel_delayed_work_sync(&bdev->wq);

	while (ttm_bo_delayed_delete(bdev, true))
		;

	spin_lock(&glob->lru_lock);
	if (list_empty(&bdev->ddestroy))
		TTM_DEBUG("Delayed destroy list was clean\n");

	if (list_empty(&bdev->man[0].lru))
		TTM_DEBUG("Swap list was clean\n");
	spin_unlock(&glob->lru_lock);

	drm_vma_offset_manager_destroy(&bdev->vma_manager);

	return ret;
}
