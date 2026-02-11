buf_buddy_alloc_from(

	buf_pool_t*	buf_pool,
	void*		buf,
	ulint		i,

	ulint		j)

{
	ulint	offs	= BUF_BUDDY_LOW << j;
	ut_ad(j <= BUF_BUDDY_SIZES);
	ut_ad(i >= buf_buddy_get_slot(PAGE_ZIP_MIN_SIZE));
	ut_ad(j >= i);
	ut_ad(!ut_align_offset(buf, offs));


	while (j > i) {
		buf_page_t*	bpage;

		offs >>= 1;
		j--;

		bpage = (buf_page_t*) ((byte*) buf + offs);
		ut_d(memset(bpage, j, BUF_BUDDY_LOW << j));
		bpage->state = BUF_BLOCK_ZIP_FREE;
		ut_d(BUF_BUDDY_LIST_VALIDATE(buf_pool, i));
		buf_buddy_add_to_free(buf_pool, bpage, j);
	}

	return(buf);
}
