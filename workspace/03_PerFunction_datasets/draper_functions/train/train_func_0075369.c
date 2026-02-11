btr_cur_open_at_index_side_func(

	ibool		from_left,

	dict_index_t*	index,
	ulint		latch_mode,
	btr_cur_t*	cursor,
	const char*	file,
	ulint		line,
	mtr_t*		mtr)
{
	page_cur_t*	page_cursor;
	ulint		page_no;
	ulint		space;
	ulint		zip_size;
	ulint		height;
	ulint		root_height = 0;
	rec_t*		node_ptr;
	ulint		estimate;
	ulint		savepoint;
	mem_heap_t*	heap		= NULL;
	ulint		offsets_[REC_OFFS_NORMAL_SIZE];
	ulint*		offsets		= offsets_;
	rec_offs_init(offsets_);

	estimate = latch_mode & BTR_ESTIMATE;
	latch_mode = latch_mode & ~BTR_ESTIMATE;


	savepoint = mtr_set_savepoint(mtr);

	if (latch_mode == BTR_MODIFY_TREE) {
		mtr_x_lock(dict_index_get_lock(index), mtr);
	} else {
		mtr_s_lock(dict_index_get_lock(index), mtr);
	}

	page_cursor = btr_cur_get_page_cur(cursor);
	cursor->index = index;

	space = dict_index_get_space(index);
	zip_size = dict_table_zip_size(index->table);
	page_no = dict_index_get_page(index);

	height = ULINT_UNDEFINED;

	for (;;) {
		buf_block_t*	block;
		page_t*		page;
		block = buf_page_get_gen(space, zip_size, page_no,
					 RW_NO_LATCH, NULL, BUF_GET,
					 file, line, mtr);
		page = buf_block_get_frame(block);
		ut_ad(index->id == btr_page_get_index_id(page));

		block->check_index_page_at_flush = TRUE;

		if (height == ULINT_UNDEFINED) {


			height = btr_page_get_level(page, mtr);
			root_height = height;
		}

		if (height == 0) {
			btr_cur_latch_leaves(page, space, zip_size, page_no,
					     latch_mode, cursor, mtr);


			if ((latch_mode != BTR_MODIFY_TREE)
			    && (latch_mode != BTR_CONT_MODIFY_TREE)) {


				mtr_release_s_latch_at_savepoint(
					mtr, savepoint,
					dict_index_get_lock(index));
			}
		}

		if (from_left) {
			page_cur_set_before_first(block, page_cursor);
		} else {
			page_cur_set_after_last(block, page_cursor);
		}

		if (height == 0) {
			if (estimate) {
				btr_cur_add_path_info(cursor, height,
						      root_height);
			}

			break;
		}

		ut_ad(height > 0);

		if (from_left) {
			page_cur_move_to_next(page_cursor);
		} else {
			page_cur_move_to_prev(page_cursor);
		}

		if (estimate) {
			btr_cur_add_path_info(cursor, height, root_height);
		}

		height--;

		node_ptr = page_cur_get_rec(page_cursor);
		offsets = rec_get_offsets(node_ptr, cursor->index, offsets,
					  ULINT_UNDEFINED, &heap);

		page_no = btr_node_ptr_get_child_page_no(node_ptr, offsets);
	}

	if (UNIV_LIKELY_NULL(heap)) {
		mem_heap_free(heap);
	}
}
