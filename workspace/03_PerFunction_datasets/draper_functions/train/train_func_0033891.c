samegame_newstate (Pos *pos, byte *move)
{
	int i, score = 0;
	gboolean bonus = FALSE;
	for (i=0; move[3*i] >= 0; i++)
	{
		if (move[3*i] == 0 && move[3*i + 1] == 0 && move[3*i + 2] == 0)
			bonus = TRUE;
		if (move[3*i+2] == 0)
			score++;
		else if (pos->board[move[3*i+1] * board_wid + move[3*i]] == 0)
			score--;
	}
	score -= 2; score *= score;
	if (score < 0) score = 0;
	state.score = (pos->state ? ((Samegame_state *)pos->state)->score : 0) + score;
	if (bonus)
		state.score += 1000;
	return &state;
}
