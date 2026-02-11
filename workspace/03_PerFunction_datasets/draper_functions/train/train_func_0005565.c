radeon_evict_flags(struct ttm_buffer_object *bo,
				struct ttm_placement *placement)
{
	static struct ttm_place placements = {
		.fpfn = 0,
		.lpfn = 0,
		.flags = TTM_PL_MASK_CACHING | TTM_PL_FLAG_SYSTEM
	};

	struct radeon_bo *rbo;

	if (!radeon_ttm_bo_is_radeon_bo(bo)) {
		placement->placement = &placements;
		placement->busy_placement = &placements;
		placement->num_placement = 1;
		placement->num_busy_placement = 1;
		return;
	}
	rbo = container_of(bo, struct radeon_bo, tbo);
	switch (bo->mem.mem_type) {
	case TTM_PL_VRAM:
		if (rbo->rdev->ring[radeon_copy_ring_index(rbo->rdev)].ready == false)
			radeon_ttm_placement_from_domain(rbo, RADEON_GEM_DOMAIN_CPU);
		else if (rbo->rdev->mc.visible_vram_size < rbo->rdev->mc.real_vram_size &&
			 bo->mem.start < (rbo->rdev->mc.visible_vram_size >> PAGE_SHIFT)) {
			unsigned fpfn = rbo->rdev->mc.visible_vram_size >> PAGE_SHIFT;
			int i;


			radeon_ttm_placement_from_domain(rbo, RADEON_GEM_DOMAIN_VRAM |
							 RADEON_GEM_DOMAIN_GTT);
			rbo->placement.num_busy_placement = 0;
			for (i = 0; i < rbo->placement.num_placement; i++) {
				if (rbo->placements[i].flags & TTM_PL_FLAG_VRAM) {
					if (rbo->placements[i].fpfn < fpfn)
						rbo->placements[i].fpfn = fpfn;
				} else {
					rbo->placement.busy_placement =
						&rbo->placements[i];
					rbo->placement.num_busy_placement = 1;
				}
			}
		} else
			radeon_ttm_placement_from_domain(rbo, RADEON_GEM_DOMAIN_GTT);
		break;
	case TTM_PL_TT:
	default:
		radeon_ttm_placement_from_domain(rbo, RADEON_GEM_DOMAIN_CPU);
	}
	*placement = rbo->placement;
}
