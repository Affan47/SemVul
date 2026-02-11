filllib_confirm_safety(int move, int color, int *defense_point)
{
  int k;
  int apos = NO_MOVE;
  int save_verbose;

  gg_assert(stackp == 0);
  gg_assert(defense_point != NULL);
  *defense_point = NO_MOVE;


  for (k = 0; k < 4; k++)
    if (board[move + delta[k]] == color) {
      apos = move + delta[k];
      break;
    }


  if (apos == NO_MOVE)
    for (k = 0; k < 4; k++) {
      int pos2 = move + delta[k];
      if (board[pos2] == OTHER_COLOR(color)
	  && !play_attack_defend_n(color, 0, 1, move, pos2)) {
	int adj;
	adj = chainlinks(pos2, adjs);


	if (adj == 0)
	  return 0;

	apos = adjs[0];
	break;
      }
    }


  if (apos == NO_MOVE) {
    for (k = 4; k < 8; k++)
      if (board[move + delta[k]] == color) {
	apos = move + delta[k];
	break;
      }
  }


  if (apos == NO_MOVE) {
    for (k = 0; k < 4; k++)
      if (board[move + 2 * delta[k]] == color) {
	apos = move + 2 * delta[k];
	break;
      }
  }


  if (apos == NO_MOVE)
    return 0;


  save_verbose = verbose;
  if (verbose > 0)
    verbose--;
  if (!owl_does_defend(move, apos, NULL))
    return 0;
  verbose = save_verbose;

  return confirm_safety(move, color, defense_point, NULL);
}
