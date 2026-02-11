mgag200_mm_init(struct mga_device *mdev)
{
	int ret;
	struct drm_device *dev = mdev->dev;
	struct ttm_bo_device *bdev = &mdev->ttm.bdev;

	ret = mgag200_ttm_global_init(mdev);
	if (ret)
		return ret;

	ret = ttm_bo_device_init(&mdev->ttm.bdev,
				 mdev->ttm.bo_global_ref.ref.object,
				 &mgag200_bo_driver,
				 dev->anon_inode->i_mapping,
				 DRM_FILE_PAGE_OFFSET,
				 true);
	if (ret) {
		DRM_ERROR("Error initialising bo driver; %d\n", ret);
		return ret;
	}

	ret = ttm_bo_init_mm(bdev, TTM_PL_VRAM, mdev->mc.vram_size >> PAGE_SHIFT);
	if (ret) {
		DRM_ERROR("Failed ttm VRAM init: %d\n", ret);
		return ret;
	}

	mdev->fb_mtrr = arch_phys_wc_add(pci_resource_start(dev->pdev, 0),
					 pci_resource_len(dev->pdev, 0));

	return 0;
}
