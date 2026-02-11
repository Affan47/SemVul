amdgpu_bo_create_restricted(struct amdgpu_device *adev,
				unsigned long size, int byte_align,
				bool kernel, u32 domain, u64 flags,
				struct sg_table *sg,
				struct ttm_placement *placement,
				struct reservation_object *resv,
				struct amdgpu_bo **bo_ptr)
{
	struct amdgpu_bo *bo;
	enum ttm_bo_type type;
	unsigned long page_align;
	size_t acc_size;
	int r;

	page_align = roundup(byte_align, PAGE_SIZE) >> PAGE_SHIFT;
	size = ALIGN(size, PAGE_SIZE);

	if (kernel) {
		type = ttm_bo_type_kernel;
	} else if (sg) {
		type = ttm_bo_type_sg;
	} else {
		type = ttm_bo_type_device;
	}
	*bo_ptr = NULL;

	acc_size = ttm_bo_dma_acc_size(&adev->mman.bdev, size,
				       sizeof(struct amdgpu_bo));

	bo = kzalloc(sizeof(struct amdgpu_bo), GFP_KERNEL);
	if (bo == NULL)
		return -ENOMEM;
	r = drm_gem_object_init(adev->ddev, &bo->gem_base, size);
	if (unlikely(r)) {
		kfree(bo);
		return r;
	}
	bo->adev = adev;
	INIT_LIST_HEAD(&bo->list);
	INIT_LIST_HEAD(&bo->va);
	bo->initial_domain = domain & (AMDGPU_GEM_DOMAIN_VRAM |
				       AMDGPU_GEM_DOMAIN_GTT |
				       AMDGPU_GEM_DOMAIN_CPU |
				       AMDGPU_GEM_DOMAIN_GDS |
				       AMDGPU_GEM_DOMAIN_GWS |
				       AMDGPU_GEM_DOMAIN_OA);

	bo->flags = flags;


	if (!drm_arch_can_wc_memory())
		bo->flags &= ~AMDGPU_GEM_CREATE_CPU_GTT_USWC;

	amdgpu_fill_placement_to_bo(bo, placement);

	r = ttm_bo_init(&adev->mman.bdev, &bo->tbo, size, type,
			&bo->placement, page_align, !kernel, NULL,
			acc_size, sg, resv, &amdgpu_ttm_bo_destroy);
	if (unlikely(r != 0)) {
		return r;
	}
	*bo_ptr = bo;

	trace_amdgpu_bo_create(bo);

	return 0;
}
