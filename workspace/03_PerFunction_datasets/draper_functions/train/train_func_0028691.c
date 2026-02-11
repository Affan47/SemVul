matchpat_loop(matchpat_callback_fn_ptr callback, int color, int anchor,
	      struct pattern_db *pdb, void *callback_data,
	      signed char goal[BOARDMAX], int anchor_in_goal)
{
  int pos;

  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    if (board[pos] == anchor && (!anchor_in_goal || goal[pos] != 0))
      do_matchpat(pos, callback, color, pdb->patterns,
		  callback_data, goal);
  }
}
