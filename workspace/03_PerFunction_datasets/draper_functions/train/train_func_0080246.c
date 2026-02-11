draw_back_moves(int str, struct reading_moves *moves)
{
  int r, k;
  int adj, adjs[MAXCHAIN];
  int libs[2];

  adj = chainlinks2(str, adjs, 2);
  for (r = 0; r < adj; r++) {
    findlib(adjs[r], 2, libs);
    for (k = 0; k < 2; k++) {
      if (!liberty_of_string(libs[k], str)
	     && ((ON_BOARD1(SOUTH(libs[k]))
		     && liberty_of_string(SOUTH(libs[k]), str))
	      || (ON_BOARD1(WEST(libs[k]))
	      	     && liberty_of_string(WEST(libs[k]), str))
	      || (ON_BOARD1(NORTH(libs[k]))
	             && liberty_of_string(NORTH(libs[k]), str))
	      || (ON_BOARD1(EAST(libs[k]))
	             && liberty_of_string(EAST(libs[k]), str)))) {
	ADD_CANDIDATE_MOVE(libs[k], 0, *moves, "draw_back");
      }
    }
  }
}
