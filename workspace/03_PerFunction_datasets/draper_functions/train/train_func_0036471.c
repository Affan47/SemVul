btr_search_drop_page_hash_when_freed(

	ulint	space,
	ulint	zip_size,

	ulint	page_no)
{
	buf_block_t*	block;
	mtr_t		mtr;

	mtr_start(&mtr);


	block = buf_page_get_gen(space, zip_size, page_no, RW_X_LATCH, NULL,
				 BUF_PEEK_IF_IN_POOL, __FILE__, __LINE__,
				 &mtr);

	if (block && block->index) {

		buf_block_dbg_add_level(block, SYNC_TREE_NODE_FROM_HASH);

		btr_search_drop_page_hash_index(block);
	}

	mtr_commit(&mtr);
}
