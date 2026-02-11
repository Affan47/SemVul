board_play_f(struct board *board, struct move *m, int f)
{
	if (DEBUGL(7)) {
		fprintf(stderr, "board_play(%s): ---- Playing %d,%d\n", coord2sstr(m->coord, board), coord_x(m->coord, board), coord_y(m->coord, board));
	}
	if (likely(!board_is_eyelike(board, m->coord, stone_other(m->color)))) {


		group_t group = board_play_outside(board, m, f);
		if (unlikely(board_group_captured(board, group))) {
			board_group_capture(board, group);
		}
		board_hash_commit(board);
		board_traits_recompute(board);
		return 0;
	} else {
		return board_play_in_eye(board, m, f);
	}
}
