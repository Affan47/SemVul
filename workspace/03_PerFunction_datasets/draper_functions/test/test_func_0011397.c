nouveau_bo_move_flips(struct ttm_buffer_object *bo, bool evict, bool intr,
		      bool no_wait_gpu, struct ttm_mem_reg *new_mem)
{
	struct ttm_place placement_memtype = {
		.fpfn = 0,
		.lpfn = 0,
		.flags = TTM_PL_FLAG_TT | TTM_PL_MASK_CACHING
	};
	struct ttm_placement placement;
	struct ttm_mem_reg tmp_mem;
	int ret;

	placement.num_placement = placement.num_busy_placement = 1;
	placement.placement = placement.busy_placement = &placement_memtype;

	tmp_mem = *new_mem;
	tmp_mem.mm_node = NULL;
	ret = ttm_bo_mem_space(bo, &placement, &tmp_mem, intr, no_wait_gpu);
	if (ret)
		return ret;

	ret = ttm_bo_move_ttm(bo, true, no_wait_gpu, &tmp_mem);
	if (ret)
		goto out;

	ret = nouveau_bo_move_m2mf(bo, true, intr, no_wait_gpu, new_mem);
	if (ret)
		goto out;

out:
	ttm_bo_mem_put(bo, &tmp_mem);
	return ret;
}
