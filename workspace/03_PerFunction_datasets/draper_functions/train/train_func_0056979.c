othello_eval (Pos *pos, Player player, float *eval)
{
	int i;
	gboolean found;

	if (pos->num_moves >= board_wid * board_heit)
	{
		for (i=0, found=FALSE; i<board_wid*board_heit; i++)
			if (pos->board [i] == OTHELLO_EMPTY) {found = TRUE; break;}
		if (!found)
		{
			*eval = othello_eval_material (pos);
			*eval *= GAME_EVAL_INFTY;
			if (*eval > 0) return RESULT_WHITE;
			if (*eval < 0) return RESULT_BLACK;
			return RESULT_NOTYET;
		}
	}

	*eval =
		10 * othello_eval_liberty (pos)

		+ 100 * othello_eval_safe (pos)
		+ othello_eval_weights (pos);
	return RESULT_NOTYET;
}
