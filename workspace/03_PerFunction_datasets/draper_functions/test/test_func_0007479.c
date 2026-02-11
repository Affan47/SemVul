modify_eyefilling_move(int *move, int color)
{
  int k;
  int r;
  int other = OTHER_COLOR(color);

  for (k = 0; k < 4; k++)
    if (ON_BOARD(*move + delta[k]) && board[*move + delta[k]] != color)
      return 0;

  for (r = 4; r < 8; r++)
    if (board[*move + delta[r]] == other
	&& countlib(*move + delta[r]) == 1) {
      for (k = 0; k < 4; k++)
	if (board[*move + delta[k]] == color
	    && countlib(*move + delta[k]) == 1
	    && !adjacent_strings(*move + delta[r], *move + delta[k]))
	  break;

      if (k == 4) {
	int new_move;
	findlib(*move + delta[r], 1, &new_move);
	TRACE("Changing eyefilling move at %1m to capture at %1m.\n",
	      *move, new_move);
	*move = new_move;
	return 1;
      }
    }

  return 0;
}
