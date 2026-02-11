ttm_bo_force_list_clean(struct ttm_bo_device *bdev,
					unsigned mem_type, bool allow_errors)
{
	struct ttm_mem_type_manager *man = &bdev->man[mem_type];
	struct ttm_bo_global *glob = bdev->glob;
	int ret;


	spin_lock(&glob->lru_lock);
	while (!list_empty(&man->lru)) {
		spin_unlock(&glob->lru_lock);
		ret = ttm_mem_evict_first(bdev, mem_type, NULL, false, false);
		if (ret) {
			if (allow_errors) {
				return ret;
			} else {
				pr_err("Cleanup eviction failed\n");
			}
		}
		spin_lock(&glob->lru_lock);
	}
	spin_unlock(&glob->lru_lock);
	return 0;
}
