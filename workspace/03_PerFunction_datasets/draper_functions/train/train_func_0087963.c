ast_mm_init(struct ast_private *ast)
{
	int ret;
	struct drm_device *dev = ast->dev;
	struct ttm_bo_device *bdev = &ast->ttm.bdev;

	ret = ast_ttm_global_init(ast);
	if (ret)
		return ret;

	ret = ttm_bo_device_init(&ast->ttm.bdev,
				 ast->ttm.bo_global_ref.ref.object,
				 &ast_bo_driver,
				 dev->anon_inode->i_mapping,
				 DRM_FILE_PAGE_OFFSET,
				 true);
	if (ret) {
		DRM_ERROR("Error initialising bo driver; %d\n", ret);
		return ret;
	}

	ret = ttm_bo_init_mm(bdev, TTM_PL_VRAM,
			     ast->vram_size >> PAGE_SHIFT);
	if (ret) {
		DRM_ERROR("Failed ttm VRAM init: %d\n", ret);
		return ret;
	}

	ast->fb_mtrr = arch_phys_wc_add(pci_resource_start(dev->pdev, 0),
					pci_resource_len(dev->pdev, 0));

	return 0;
}
