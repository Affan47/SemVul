get_temp_board(byte_board_info *board)
{
	while (!trans_free_list) {
		free_hash_move(max_hash_move);
		max_hash_move--;
	}

	trans_board *t = trans_free_list;
	trans_free_list = t->next;
	t->board = *board;
	return t;
}
