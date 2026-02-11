special_rescue_moves(int str, int lib, struct reading_moves *moves)
{
  int color = board[str];
  int other = OTHER_COLOR(color);
  int otherlib;
  int k;


  otherlib = approxlib(lib, other, 3, NULL);
  if (otherlib > 2)
    return;


  for (k = 0; k < 4; k++) {
    int d = delta[k];
    if (board[lib + d] == EMPTY) {


      if (is_self_atari(lib + d, color) && otherlib > 1)
	continue;


      if (countlib(str) > 3) {
	int r;
	int number_protected = 0;

	for (r = 0; r < 4; r++) {
	  if (board[lib + d + delta[r]] == EMPTY
	      && approxlib(lib + d + delta[r], other, 3, NULL) < 3)
	    number_protected++;
	  if (number_protected == 2)
	    break;
	}

	if (number_protected < 2)
	  continue;
      }

      ADD_CANDIDATE_MOVE(lib + d, 0, *moves, "special_rescue");
    }
  }
}
