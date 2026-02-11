vmw_mob_pt_setup(struct vmw_mob *mob,
			     struct vmw_piter data_iter,
			     unsigned long num_data_pages)
{
	unsigned long num_pt_pages = 0;
	struct ttm_buffer_object *bo = mob->pt_bo;
	struct vmw_piter save_pt_iter;
	struct vmw_piter pt_iter;
	const struct vmw_sg_table *vsgt;
	int ret;

	ret = ttm_bo_reserve(bo, false, true, false, NULL);
	BUG_ON(ret != 0);

	vsgt = vmw_bo_sg_table(bo);
	vmw_piter_start(&pt_iter, vsgt, 0);
	BUG_ON(!vmw_piter_next(&pt_iter));
	mob->pt_level = 0;
	while (likely(num_data_pages > 1)) {
		++mob->pt_level;
		BUG_ON(mob->pt_level > 2);
		save_pt_iter = pt_iter;
		num_pt_pages = vmw_mob_build_pt(&data_iter, num_data_pages,
						&pt_iter);
		data_iter = save_pt_iter;
		num_data_pages = num_pt_pages;
	}

	mob->pt_root_page = vmw_piter_dma_addr(&save_pt_iter);
	ttm_bo_unreserve(bo);
}
