prevent_capture_one_move(int *moves, int str1)
{
  int r, res = 0;
  int liberties, libs[MAXLIBS];
  int adj, adjs[MAXCHAIN];

  liberties = findlib(str1, MAXLIBS, libs);
  if (liberties == 1) {
    add_array(moves, libs[0]);
    res = WIN;
    adj = chainlinks2(str1, adjs, 1);
    for (r = 0; r < adj; r++) {
      findlib(adjs[r], 1, libs);
      add_array(moves, libs[0]);
    }
  }
  return res;
}
