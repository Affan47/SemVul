compute_active_owl_area(struct persistent_cache_entry *entry,
			const signed char goal[BOARDMAX], int goal_color)
{
  int pos;
  signed char active[BOARDMAX];
  memset(active, 0, BOARDMAX);


  if (ON_BOARD1(entry->move))
    active[entry->move] = 1;

  if (ON_BOARD1(entry->move2))
    active[entry->move2] = 1;

  compute_active_owl_type_area(goal, goal_color, active);

  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    int value = board[pos];
    if (!ON_BOARD(pos))
      continue;
    if (!active[pos])
      value = GRAY;
    else if (IS_STONE(board[pos]) && countlib(pos) > 4 && active[pos] > 0)
      value |= HIGH_LIBERTY_BIT;

    entry->board[pos] = value;
  }
}
