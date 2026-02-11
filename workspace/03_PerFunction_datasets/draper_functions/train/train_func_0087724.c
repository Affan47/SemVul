amdgpu_fill_placement_to_bo(struct amdgpu_bo *bo,
					struct ttm_placement *placement)
{
	BUG_ON(placement->num_placement > (AMDGPU_GEM_DOMAIN_MAX + 1));

	memcpy(bo->placements, placement->placement,
	       placement->num_placement * sizeof(struct ttm_place));
	bo->placement.num_placement = placement->num_placement;
	bo->placement.num_busy_placement = placement->num_busy_placement;
	bo->placement.placement = bo->placements;
	bo->placement.busy_placement = bo->placements;
}
