page_parse_delete_rec_list(

	byte		type,


	byte*		ptr,
	byte*		end_ptr,
	buf_block_t*	block,
	dict_index_t*	index,
	mtr_t*		mtr)
{
	page_t*	page;
	ulint	offset;

	ut_ad(type == MLOG_LIST_END_DELETE
	      || type == MLOG_LIST_START_DELETE
	      || type == MLOG_COMP_LIST_END_DELETE
	      || type == MLOG_COMP_LIST_START_DELETE);


	if (end_ptr < ptr + 2) {

		return(NULL);
	}

	offset = mach_read_from_2(ptr);
	ptr += 2;

	if (!block) {

		return(ptr);
	}

	page = buf_block_get_frame(block);

	ut_ad(!!page_is_comp(page) == dict_table_is_comp(index->table));

	if (type == MLOG_LIST_END_DELETE
	    || type == MLOG_COMP_LIST_END_DELETE) {
		page_delete_rec_list_end(page + offset, block, index,
					 ULINT_UNDEFINED, ULINT_UNDEFINED,
					 mtr);
	} else {
		page_delete_rec_list_start(page + offset, block, index, mtr);
	}

	return(ptr);
}
