amdgpu_cgs_alloc_gpu_mem(void *cgs_device,
				    enum cgs_gpu_mem_type type,
				    uint64_t size, uint64_t align,
				    uint64_t min_offset, uint64_t max_offset,
				    cgs_handle_t *handle)
{
	CGS_FUNC_ADEV;
	uint16_t flags = 0;
	int ret = 0;
	uint32_t domain = 0;
	struct amdgpu_bo *obj;
	struct ttm_placement placement;
	struct ttm_place place;

	if (min_offset > max_offset) {
		BUG_ON(1);
		return -EINVAL;
	}


	if (((align != 1) && (align & (align - 1)))
	    || size == 0 || align == 0)
		return -EINVAL;


	switch(type) {
	case CGS_GPU_MEM_TYPE__VISIBLE_CONTIG_FB:
	case CGS_GPU_MEM_TYPE__VISIBLE_FB:
		flags = AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
		domain = AMDGPU_GEM_DOMAIN_VRAM;
		if (max_offset > adev->mc.real_vram_size)
			return -EINVAL;
		place.fpfn = min_offset >> PAGE_SHIFT;
		place.lpfn = max_offset >> PAGE_SHIFT;
		place.flags = TTM_PL_FLAG_WC | TTM_PL_FLAG_UNCACHED |
			TTM_PL_FLAG_VRAM;
		break;
	case CGS_GPU_MEM_TYPE__INVISIBLE_CONTIG_FB:
	case CGS_GPU_MEM_TYPE__INVISIBLE_FB:
		flags = AMDGPU_GEM_CREATE_NO_CPU_ACCESS;
		domain = AMDGPU_GEM_DOMAIN_VRAM;
		if (adev->mc.visible_vram_size < adev->mc.real_vram_size) {
			place.fpfn =
				max(min_offset, adev->mc.visible_vram_size) >> PAGE_SHIFT;
			place.lpfn =
				min(max_offset, adev->mc.real_vram_size) >> PAGE_SHIFT;
			place.flags = TTM_PL_FLAG_WC | TTM_PL_FLAG_UNCACHED |
				TTM_PL_FLAG_VRAM;
		}

		break;
	case CGS_GPU_MEM_TYPE__GART_CACHEABLE:
		domain = AMDGPU_GEM_DOMAIN_GTT;
		place.fpfn = min_offset >> PAGE_SHIFT;
		place.lpfn = max_offset >> PAGE_SHIFT;
		place.flags = TTM_PL_FLAG_CACHED | TTM_PL_FLAG_TT;
		break;
	case CGS_GPU_MEM_TYPE__GART_WRITECOMBINE:
		flags = AMDGPU_GEM_CREATE_CPU_GTT_USWC;
		domain = AMDGPU_GEM_DOMAIN_GTT;
		place.fpfn = min_offset >> PAGE_SHIFT;
		place.lpfn = max_offset >> PAGE_SHIFT;
		place.flags = TTM_PL_FLAG_WC | TTM_PL_FLAG_TT |
			TTM_PL_FLAG_UNCACHED;
		break;
	default:
		return -EINVAL;
	}


	*handle = 0;

	placement.placement = &place;
	placement.num_placement = 1;
	placement.busy_placement = &place;
	placement.num_busy_placement = 1;

	ret = amdgpu_bo_create_restricted(adev, size, PAGE_SIZE,
					  true, domain, flags,
					  NULL, &placement, NULL,
					  &obj);
	if (ret) {
		DRM_ERROR("(%d) bo create failed\n", ret);
		return ret;
	}
	*handle = (cgs_handle_t)obj;

	return ret;
}
