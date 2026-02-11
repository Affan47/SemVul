flw_who_won (Pos *pos, Player to_play, char **commp)
{
	static char comment[32] = "You won.";
	int i;
	for (i=0; i<FLW_LEN; i++)
		if (pos->board [i] != pos->board [board_wid + i])
			return RESULT_NOTYET;
	*commp = comment;
	return RESULT_WON;
}
