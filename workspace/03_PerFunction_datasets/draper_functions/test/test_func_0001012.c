mc_is_self_atari(struct mc_board *mc, int pos, int color)
{
  int k;
  int captured = NO_MOVE;
  int liberty = NO_MOVE;
  int reference;
  int other;


  if (((mc->board[SOUTH(pos)] == EMPTY)
       + (mc->board[WEST(pos)] == EMPTY)
       + (mc->board[NORTH(pos)] == EMPTY)
       + (mc->board[EAST(pos)] == EMPTY)) > 1)
    return 0;


  for (k = 0; k < 4; k++) {
    int first_liberty_edge;
    int liberty_edge;
    int additional_liberty = 0;
    int pos2 = pos + delta[k];
    if (mc->board[pos2] == EMPTY) {
      if (pos2 != liberty) {
	if (liberty != NO_MOVE)
	  return 0;
	else
	  liberty = pos2;
      }
    }
    else if (IS_STONE(mc->board[pos2])) {
      first_liberty_edge = (pos << 2) | k;
      liberty_edge = mc->next_liberty_edge[first_liberty_edge];
      while (liberty_edge != first_liberty_edge) {
	int lib = liberty_edge >> 2;
	if (lib != pos) {
	  additional_liberty = 1;
	  if (mc->board[pos2] == color) {
	    if (lib != liberty) {
	      if (liberty != NO_MOVE)
		return 0;
	      else
		liberty = lib;
	    }
	  }
	  else
	    break;
	}
	liberty_edge = mc->next_liberty_edge[liberty_edge];
      }

      if (mc->board[pos2] != color && additional_liberty == 0) {
	captured = pos2;
	if (pos2 != liberty) {
	  if (liberty != NO_MOVE)
	    return 0;
	  else
	    liberty = pos2;
	}
      }
    }
  }

  if (liberty == NO_MOVE || captured == NO_MOVE)
    return 1;


  reference = mc->reference_stone[captured];
  other = OTHER_COLOR(color);
  for (k = 0; k < 4; k++) {
    if (mc->board[pos + delta[k]] == color) {
      int stone = pos + delta[k];
      do {
	int m;
	for (m = 0; m < 4; m++) {
	  int pos2 = stone + delta[m];
	  if (mc->board[pos2] == other
	      && pos2 != captured
	      && mc->reference_stone[pos2] == reference)
	    return 0;
	}
	stone = mc->next_stone[stone];
      } while (stone != pos + delta[k]);
    }
  }

  return 1;
}
