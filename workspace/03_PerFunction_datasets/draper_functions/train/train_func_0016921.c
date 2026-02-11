page_mem_alloc_heap(

	page_t*		page,
	page_zip_des_t*	page_zip,


	ulint		need,
	ulint*		heap_no)


{
	byte*	block;
	ulint	avl_space;

	ut_ad(page && heap_no);

	avl_space = page_get_max_insert_size(page, 1);

	if (avl_space >= need) {
		block = page_header_get_ptr(page, PAGE_HEAP_TOP);

		page_header_set_ptr(page, page_zip, PAGE_HEAP_TOP,
				    block + need);
		*heap_no = page_dir_get_n_heap(page);

		page_dir_set_n_heap(page, page_zip, 1 + *heap_no);

		return(block);
	}

	return(NULL);
}
