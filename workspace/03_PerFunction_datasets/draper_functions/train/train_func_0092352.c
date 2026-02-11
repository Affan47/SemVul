join_dragons(int d1, int d2)
{
  int ii;
  int origin;


  if (stackp > 0) {
    join_new_dragons(d1, d2);
    return;
  }


  d1 = dragon[d1].origin;
  d2 = dragon[d2].origin;


  if (d1 == d2)
    return;

  ASSERT1(board[d1] == board[d2], d1);
  gg_assert(dragon2_initialized == 0);
  ASSERT1(IS_STONE(board[d1]), d1);


  if (worm[d1].size > worm[d2].size
      || (worm[d1].size == worm[d2].size
	  && d1 < d2)) {
    origin = d1;
    DEBUG(DEBUG_DRAGONS, "joining dragon at %1m to dragon at %1m\n", d2, d1);
  }
  else {
    origin = d2;
    DEBUG(DEBUG_DRAGONS, "joining dragon at %1m to dragon at %1m\n", d1, d2);
  }

  dragon[origin].size  = dragon[d2].size + dragon[d1].size;
  dragon[origin].effective_size  = (dragon[d2].effective_size
				    + dragon[d1].effective_size);


  {
    int last_worm_origin_dragon = origin;
    while (next_worm_list[last_worm_origin_dragon] != NO_MOVE)
      last_worm_origin_dragon = next_worm_list[last_worm_origin_dragon];
    if (origin == d1)
      next_worm_list[last_worm_origin_dragon] = d2;
    else
      next_worm_list[last_worm_origin_dragon] = d1;
  }

  for (ii = BOARDMIN; ii < BOARDMAX; ii++) {
    if (ON_BOARD(ii)
	&& (dragon[ii].origin == d1 || dragon[ii].origin == d2))
      dragon[ii].origin = origin;
  }
}
