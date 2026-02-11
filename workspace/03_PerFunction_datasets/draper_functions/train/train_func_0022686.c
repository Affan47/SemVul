virtio_gpu_init_mem_type(struct ttm_bo_device *bdev, uint32_t type,
				    struct ttm_mem_type_manager *man)
{
	struct virtio_gpu_device *vgdev;

	vgdev = virtio_gpu_get_vgdev(bdev);

	switch (type) {
	case TTM_PL_SYSTEM:

		man->flags = TTM_MEMTYPE_FLAG_MAPPABLE;
		man->available_caching = TTM_PL_MASK_CACHING;
		man->default_caching = TTM_PL_FLAG_CACHED;
		break;
	case TTM_PL_TT:
		man->func = &virtio_gpu_bo_manager_func;
		man->flags = TTM_MEMTYPE_FLAG_MAPPABLE;
		man->available_caching = TTM_PL_MASK_CACHING;
		man->default_caching = TTM_PL_FLAG_CACHED;
		break;
	default:
		DRM_ERROR("Unsupported memory type %u\n", (unsigned)type);
		return -EINVAL;
	}
	return 0;
}
