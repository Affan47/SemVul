plot4_who_won (Pos *pos, Player to_play, char **commp)
{
	static char comment[32];
	char *who_str [3] = { "Green won", "Yellow won", "Its a tie" };
	int i, wscore, bscore, who_idx;
	wscore = eval_runs (pos, WHITE) / RUN_WT;
	bscore = eval_runs (pos, BLACK) / RUN_WT * -1;
	*commp = comment;
	for (i=0; i<board_wid * board_heit; i++)
		if (pos->board[i] == PLOT4_EMPTY)
		{
			snprintf (comment, 32, "%d : %d", wscore, bscore);
			return RESULT_NOTYET;
		}
	if (wscore > bscore) who_idx = 0;
	else if (wscore < bscore) who_idx = 1;
	else who_idx = 2;
	snprintf (comment, 32, "%s (%d : %d)", who_str[who_idx], wscore, bscore);
	if (wscore > bscore)
		return RESULT_WHITE;
	if (wscore < bscore)
		return RESULT_BLACK;
	return RESULT_TIE;
}
