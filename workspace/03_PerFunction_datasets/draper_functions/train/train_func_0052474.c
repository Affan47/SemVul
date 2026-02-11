owl_shapes_callback(int anchor, int color, struct pattern *pattern,
		    int ll, void *data)
{
  int tval;
  int move;
  struct owl_move_data *moves = data;
  enum same_dragon_value same_dragon = SAME_DRAGON_MAYBE_CONNECTED;
  int escape = 0;
  int defense_pos;


  move = AFFINE_TRANSFORM(pattern->move_offset, ll, anchor);


  if (!allpats) {
    int k;
    for (k = 0; k < MAX_MOVES; k++) {
      if (moves[k].value == -1)
	break;
      if (moves[k].pos == move) {
	if (moves[k].value >= pattern->value)
	  return;
	else
	  break;
      }
    }
    if (k == MAX_MOVES && moves[MAX_MOVES - 1].value >= pattern->value)
      return;
  }

  if (!check_pattern_hard(move, color, pattern, ll))
    return;


  if (pattern->helper) {

    gg_assert(0);
    DEBUG(DEBUG_HELPER, "  asking helper to consider '%s'+%d at %1m\n",
	  pattern->name, ll, move);
    tval = pattern->helper(pattern, ll, move, color);

    if (tval > 0) {
      DEBUG(DEBUG_HELPER, "helper likes pattern '%s' value %d at %1m\n",
	    pattern->name, tval, move);
    }
    else {
      DEBUG(DEBUG_HELPER, "  helper does not like pattern '%s' at %1m\n",
	    pattern->name, move);
      return;
    }
  }
  else {
    tval = (int) pattern->value;
  }


  TRACE("Pattern %s found at %1m with value %d\n", pattern->name, move, tval);

  if (pattern->class & CLASS_B)
    same_dragon = SAME_DRAGON_NOT_CONNECTED;
  else if (pattern->class & CLASS_b)
    same_dragon = SAME_DRAGON_MAYBE_CONNECTED;
  else if (pattern->class & CLASS_a) {
    same_dragon = SAME_DRAGON_ALL_CONNECTED;


    gg_assert(0);
  }
  else
    same_dragon = SAME_DRAGON_CONNECTED;

  if (pattern->class & CLASS_E)
    escape = 1;
  else
    escape = 0;


  {
    int k;
    defense_pos = move;
    for (k = 0; k < pattern->patlen; k++)
      if (pattern->patn[k].att == ATT_not)
	defense_pos = AFFINE_TRANSFORM(pattern->patn[k].offset, ll, anchor);
  }

  owl_add_move(moves, move, tval, pattern->name, same_dragon, NO_MOVE,
      	       escape, defense_pos, MAX_MOVES, NULL);
}
