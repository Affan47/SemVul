store_persistent_semeai_cache(enum routine_id routine,
    			      int apos, int bpos, int cpos, int color,
			      Hash_data *goal_hash,
    			      int resulta, int resultb, int move, int certain,
			      int tactical_nodes,
			      signed char goala[BOARDMAX],
			      signed char goalb[BOARDMAX])
{
  signed char goal[BOARDMAX];
  int pos;

  for (pos = BOARDMIN; pos < BOARDMAX; pos++)
    if (ON_BOARD(pos))
      goal[pos] = goala[pos] || goalb[pos];

  store_persistent_cache(&semeai_cache, routine,
      			 apos, bpos, cpos, color, goal_hash,
			 resulta, resultb, move, NO_MOVE,
			 certain, semeai_node_limit,
			 tactical_nodes, goal, EMPTY);
}
