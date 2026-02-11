ttm_bo_mem_space_debug(struct ttm_buffer_object *bo,
					struct ttm_placement *placement)
{
	int i, ret, mem_type;

	pr_err("No space for %p (%lu pages, %luK, %luM)\n",
	       bo, bo->mem.num_pages, bo->mem.size >> 10,
	       bo->mem.size >> 20);
	for (i = 0; i < placement->num_placement; i++) {
		ret = ttm_mem_type_from_place(&placement->placement[i],
						&mem_type);
		if (ret)
			return;
		pr_err("  placement[%d]=0x%08X (%d)\n",
		       i, placement->placement[i].flags, mem_type);
		ttm_mem_type_debug(bo->bdev, mem_type);
	}
}
