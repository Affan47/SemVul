buf_LRU_remove_block(

	buf_page_t*	bpage)
{
	buf_pool_t*	buf_pool = buf_pool_from_bpage(bpage);
	ulint		zip_size;

	ut_ad(buf_pool);
	ut_ad(bpage);
	ut_ad(buf_pool_mutex_own(buf_pool));

	ut_a(buf_page_in_file(bpage));

	ut_ad(bpage->in_LRU_list);


	if (UNIV_UNLIKELY(bpage == buf_pool->LRU_old)) {


		buf_page_t*	prev_bpage = UT_LIST_GET_PREV(LRU, bpage);

		ut_a(prev_bpage);
#ifdef UNIV_LRU_DEBUG
		ut_a(!prev_bpage->old);
#endif
		buf_pool->LRU_old = prev_bpage;
		buf_page_set_old(prev_bpage, TRUE);

		buf_pool->LRU_old_len++;
	}


	UT_LIST_REMOVE(LRU, buf_pool->LRU, bpage);
	ut_d(bpage->in_LRU_list = FALSE);

	zip_size = page_zip_get_size(&bpage->zip);
	buf_pool->stat.LRU_bytes -= zip_size ? zip_size : UNIV_PAGE_SIZE;

	buf_unzip_LRU_remove_block_if_needed(bpage);


	if (UT_LIST_GET_LEN(buf_pool->LRU) < BUF_LRU_OLD_MIN_LEN) {

		for (bpage = UT_LIST_GET_FIRST(buf_pool->LRU); bpage != NULL;
		     bpage = UT_LIST_GET_NEXT(LRU, bpage)) {


			bpage->old = FALSE;
		}

		buf_pool->LRU_old = NULL;
		buf_pool->LRU_old_len = 0;

		return;
	}

	ut_ad(buf_pool->LRU_old);


	if (buf_page_is_old(bpage)) {

		buf_pool->LRU_old_len--;
	}


	buf_LRU_old_adjust_len(buf_pool);
}
