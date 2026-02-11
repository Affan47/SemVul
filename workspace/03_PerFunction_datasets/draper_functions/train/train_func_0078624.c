balance_leaf_new_nodes_paste_dirent(struct tree_balance *tb,
					 struct item_head * const ih,
					 const char * const body,
					 struct item_head *insert_key,
					 struct buffer_head **insert_ptr,
					 int i)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	struct item_head *aux_ih = item_head(tbS0, tb->item_pos);
	int entry_count = ih_entry_count(aux_ih);
	struct buffer_info bi;

	if (entry_count - tb->sbytes[i] < tb->pos_in_item &&
	    tb->pos_in_item <= entry_count) {


		RFALSE(!tb->insert_size[0],
		       "PAP-12215: insert_size is already 0");
		RFALSE(tb->sbytes[i] - 1 >= entry_count,
		       "PAP-12220: there are no so much entries (%d), only %d",
		       tb->sbytes[i] - 1, entry_count);


		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i],
				tb->sbytes[i] - 1, tb->S_new[i]);


		buffer_info_init_bh(tb, &bi, tb->S_new[i]);
		leaf_paste_in_buffer(&bi, 0, tb->pos_in_item - entry_count +
				     tb->sbytes[i] - 1, tb->insert_size[0],
				     body, tb->zeroes_num);


		leaf_paste_entries(&bi, 0, tb->pos_in_item - entry_count +
				   tb->sbytes[i] - 1, 1,
				   (struct reiserfs_de_head *) body,
				   body + DEH_SIZE, tb->insert_size[0]);

		tb->insert_size[0] = 0;
		tb->pos_in_item++;
	} else {

		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i],
				tb->sbytes[i], tb->S_new[i]);
	}

}
