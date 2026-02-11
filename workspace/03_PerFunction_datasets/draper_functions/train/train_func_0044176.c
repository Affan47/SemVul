antichess_eval_incr (Pos *pos, Player player, byte *move, float *eval)

{
	byte *board = pos->board;
	if (player == WHITE)
	{
		if (move[2] && board[move[1] * board_wid + move[0]]) *eval = -1;
		else if (move[5] && board[move[4] * board_wid + move[3]]) return -1;
		else *eval = 0;
	}
	else
	{
		if (move[2] && board[move[1] * board_wid + move[0]]) *eval = 1;
		else if (move[5] && board[move[4] * board_wid + move[3]]) *eval = 1;
		else *eval = 0;
	}
	return RESULT_NOTYET;
}
