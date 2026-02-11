qxl_bo_unpin(struct qxl_bo *bo)
{
	struct qxl_device *qdev = (struct qxl_device *)bo->gem_base.dev->dev_private;
	int r, i;

	if (!bo->pin_count) {
		dev_warn(qdev->dev, "%p unpin not necessary\n", bo);
		return 0;
	}
	bo->pin_count--;
	if (bo->pin_count)
		return 0;
	for (i = 0; i < bo->placement.num_placement; i++)
		bo->placements[i].flags &= ~TTM_PL_FLAG_NO_EVICT;
	r = ttm_bo_validate(&bo->tbo, &bo->placement, false, false);
	if (unlikely(r != 0))
		dev_err(qdev->dev, "%p validate failed for unpin\n", bo);
	return r;
}
