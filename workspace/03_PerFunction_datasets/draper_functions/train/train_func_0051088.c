ataxx_who_won (Pos *pos, Player to_play, char **commp)
{
	static char comment[32];
	int i, wscore = 0, bscore = 0, who_idx;
	char *who_str [3] = { "Red won", "Blue won", "its a tie" };
	byte *move = ataxx_movegen (pos);
	for (i=0; i<board_wid * board_heit; i++)
		if (pos->board[i] == ATAXX_WP)
			wscore++;
		else if (pos->board[i] == ATAXX_BP)
			bscore++;
	if (move[0] != -2)
	{
		free (move);
		if (pos->num_moves > ataxx_max_moves)
		{
			fprintf (stderr, "max moves reached\n");
			snprintf (comment, 32, "%s", who_str[2]);
			*commp = comment;
			return RESULT_TIE;
		}
		else
		{
			snprintf (comment, 32, "%d : %d", wscore, bscore);
			*commp = comment;
			return RESULT_NOTYET;
		}
	}
	free (move);
	if (wscore > bscore) who_idx = 0;
	else if (wscore < bscore) who_idx = 1;
	else who_idx = 2;
	snprintf (comment, 32, "%s (%d : %d)", who_str [who_idx], wscore, bscore);
	*commp = comment;
	if (wscore > bscore)
		return RESULT_WHITE;
	if (wscore < bscore)
		return RESULT_BLACK;
	return RESULT_TIE;
}
