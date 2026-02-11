infiltrate_eval (Pos *pos, Player to_play, float *eval)
{
	float sum = 0;
	int i, j;
	for (i=0; i<board_wid; i++)
	for (j=0; j<board_heit; j++)
		if (pos->board [j * board_wid + i])
			sum += j;
	*eval = sum;
	return RESULT_NOTYET;

}
