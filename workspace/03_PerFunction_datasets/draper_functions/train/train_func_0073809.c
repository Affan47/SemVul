radeon_bo_fault_reserve_notify(struct ttm_buffer_object *bo)
{
	struct radeon_device *rdev;
	struct radeon_bo *rbo;
	unsigned long offset, size, lpfn;
	int i, r;

	if (!radeon_ttm_bo_is_radeon_bo(bo))
		return 0;
	rbo = container_of(bo, struct radeon_bo, tbo);
	radeon_bo_check_tiling(rbo, 0, 0);
	rdev = rbo->rdev;
	if (bo->mem.mem_type != TTM_PL_VRAM)
		return 0;

	size = bo->mem.num_pages << PAGE_SHIFT;
	offset = bo->mem.start << PAGE_SHIFT;
	if ((offset + size) <= rdev->mc.visible_vram_size)
		return 0;


	radeon_ttm_placement_from_domain(rbo, RADEON_GEM_DOMAIN_VRAM);
	lpfn =	rdev->mc.visible_vram_size >> PAGE_SHIFT;
	for (i = 0; i < rbo->placement.num_placement; i++) {

		if ((rbo->placements[i].flags & TTM_PL_FLAG_VRAM) &&
		    (!rbo->placements[i].lpfn || rbo->placements[i].lpfn > lpfn))
			rbo->placements[i].lpfn = lpfn;
	}
	r = ttm_bo_validate(bo, &rbo->placement, false, false);
	if (unlikely(r == -ENOMEM)) {
		radeon_ttm_placement_from_domain(rbo, RADEON_GEM_DOMAIN_GTT);
		return ttm_bo_validate(bo, &rbo->placement, false, false);
	} else if (unlikely(r != 0)) {
		return r;
	}

	offset = bo->mem.start << PAGE_SHIFT;

	if ((offset + size) > rdev->mc.visible_vram_size)
		return -EINVAL;

	return 0;
}
