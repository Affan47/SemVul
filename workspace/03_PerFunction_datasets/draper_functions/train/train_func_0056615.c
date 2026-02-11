vmw_mob_pt_populate(struct vmw_private *dev_priv,
			       struct vmw_mob *mob)
{
	int ret;
	BUG_ON(mob->pt_bo != NULL);

	ret = ttm_bo_create(&dev_priv->bdev, mob->num_pages * PAGE_SIZE,
			    ttm_bo_type_device,
			    &vmw_sys_ne_placement,
			    0, false, NULL, &mob->pt_bo);
	if (unlikely(ret != 0))
		return ret;

	ret = ttm_bo_reserve(mob->pt_bo, false, true, false, NULL);

	BUG_ON(ret != 0);
	ret = vmw_bo_driver.ttm_tt_populate(mob->pt_bo->ttm);
	if (unlikely(ret != 0))
		goto out_unreserve;
	ret = vmw_bo_map_dma(mob->pt_bo);
	if (unlikely(ret != 0))
		goto out_unreserve;

	ttm_bo_unreserve(mob->pt_bo);

	return 0;

out_unreserve:
	ttm_bo_unreserve(mob->pt_bo);
	ttm_bo_unref(&mob->pt_bo);

	return ret;
}
