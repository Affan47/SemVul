nouveau_ttm_tt_create(struct ttm_bo_device *bdev, unsigned long size,
		      uint32_t page_flags, struct page *dummy_read)
{
#if IS_ENABLED(CONFIG_AGP)
	struct nouveau_drm *drm = nouveau_bdev(bdev);

	if (drm->agp.bridge) {
		return ttm_agp_tt_create(bdev, drm->agp.bridge, size,
					 page_flags, dummy_read);
	}
#endif

	return nouveau_sgdma_create_ttm(bdev, size, page_flags, dummy_read);
}
