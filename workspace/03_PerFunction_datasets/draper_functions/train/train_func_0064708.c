owl_update_goal(int pos, enum same_dragon_value same_dragon, int lunch,
    		struct local_owl_data *owl, int semeai_call,
		struct matched_pattern_data *pattern_data)
{
  int stones[MAX_BOARD * MAX_BOARD];
  int num_stones;
  int k;
  int do_add = 1;
  SGFTree *save_sgf_dumptree = sgf_dumptree;
  int save_count_variations = count_variations;


  sgf_dumptree = NULL;
  count_variations = 0;

  if (same_dragon == SAME_DRAGON_NOT_CONNECTED)
    num_stones = findstones(pos, MAX_BOARD * MAX_BOARD, stones);
  else if (semeai_call)
    find_superstring_conservative(pos, &num_stones, stones);
  else
    find_superstring(pos, &num_stones, stones);


  sgf_dumptree = save_sgf_dumptree;
  count_variations = save_count_variations;


  if (same_dragon <= SAME_DRAGON_MAYBE_CONNECTED) {
    do_add = 0;
    for (k = 0; k < num_stones; k++)
      if (owl->goal[stones[k]] != 0) {
	do_add = 1;
	break;
      }
  }

  if (do_add)
    for (k = 0; k < num_stones; k++) {
      if (owl->goal[stones[k]] == 0) {
	if (0)
	  TRACE("Added %1m to goal.\n", stones[k]);
	owl->goal[stones[k]] = 2;
	owl->cumulative_goal[stones[k]] = 1;
      }
    }


  if (!semeai_call && lunch != NO_MOVE && board[lunch] != EMPTY) {
    int adj, adjs[MAXCHAIN];
    int k;
    adj = chainlinks(lunch, adjs);
    for (k = 0; k < adj; k++)
      if (!owl->goal[adjs[k]]) {
	mark_string(adjs[k], owl->goal, 2);
	mark_string(adjs[k], owl->cumulative_goal, 2);
      }
  }


  if (same_dragon == SAME_DRAGON_ALL_CONNECTED) {
    gg_assert(pattern_data != NULL);
    for (k = 0; k < pattern_data->pattern->patlen; k++) {
      int pos2;


      if (pattern_data->pattern->patn[k].att != ATT_O)
	continue;


      pos2 = AFFINE_TRANSFORM(pattern_data->pattern->patn[k].offset,
			      pattern_data->ll, pattern_data->anchor);

      if (!owl->goal[pos2])
	owl_update_goal(pos2, SAME_DRAGON_CONNECTED, NO_MOVE, owl, semeai_call,
			pattern_data);
    }
  }

  if (1 && verbose)
    goaldump(owl->goal);
}
