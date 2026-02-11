ttm_bo_man_takedown(struct ttm_mem_type_manager *man)
{
	struct ttm_range_manager *rman = (struct ttm_range_manager *) man->priv;
	struct drm_mm *mm = &rman->mm;

	spin_lock(&rman->lock);
	if (drm_mm_clean(mm)) {
		drm_mm_takedown(mm);
		spin_unlock(&rman->lock);
		kfree(rman);
		man->priv = NULL;
		return 0;
	}
	spin_unlock(&rman->lock);
	return -EBUSY;
}
