chess_who_won (Pos *pos, Player player, char **commp)
{
	static char comment[32];
	char *who_str [3] = { "White won", "Black won", "Draw" };
	byte *move_list;
	*commp = NULL;
	move_list = chess_movegen (pos);
	if (move_list[0] != -2)
	{
		if (pos->num_moves > chess_max_moves)
		{
			fprintf (stderr, "max moves reached\n");
			snprintf (comment, 32, "%s", who_str[2]);
			*commp = comment;
			return RESULT_TIE;
		}
		return RESULT_NOTYET;
	}
	*commp = comment;
	if (is_in_check (pos, player))
	{
		strncpy (comment, who_str[player == WHITE ? 1 : 0], 31);
		return player == WHITE ? RESULT_BLACK : RESULT_WHITE;
	}
	else
	{
		strncpy (comment, who_str[2], 31);
		return RESULT_TIE;
	}
}
