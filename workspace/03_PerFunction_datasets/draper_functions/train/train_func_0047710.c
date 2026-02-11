tetris_game_over (byte *board)
{
	int i;
	for (i=0; i<TETRIS_REAL_WID; i++)
		if (board[(board_heit - 2) * board_wid + i] == TETRIS_BRICK_INACTIVE)
			return 1;
	return 0;
}
