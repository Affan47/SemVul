ast_cursor_init(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;
	int size;
	int ret;
	struct drm_gem_object *obj;
	struct ast_bo *bo;
	uint64_t gpu_addr;

	size = (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE) * AST_DEFAULT_HWC_NUM;

	ret = ast_gem_create(dev, size, true, &obj);
	if (ret)
		return ret;
	bo = gem_to_ast_bo(obj);
	ret = ast_bo_reserve(bo, false);
	if (unlikely(ret != 0))
		goto fail;

	ret = ast_bo_pin(bo, TTM_PL_FLAG_VRAM, &gpu_addr);
	ast_bo_unreserve(bo);
	if (ret)
		goto fail;


	ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &ast->cache_kmap);
	if (ret)
		goto fail;

	ast->cursor_cache = obj;
	ast->cursor_cache_gpu_addr = gpu_addr;
	DRM_DEBUG_KMS("pinned cursor cache at %llx\n", ast->cursor_cache_gpu_addr);
	return 0;
fail:
	return ret;
}
