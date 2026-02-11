find_best_move(int *the_move, float *value, int color,
	       int allowed_moves[BOARDMAX])
{
  int good_move_found = 0;
  signed char blunder_tested[BOARDMAX];
  float best_value = 0.0;
  int best_move = NO_MOVE;
  int pos;

  memset(blunder_tested, 0, sizeof(blunder_tested));

  while (!good_move_found) {
    best_value = 0.0;
    best_move = NO_MOVE;


    for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
      float this_value = move[pos].final_value;
      if (allowed_moves && !allowed_moves[pos])
	continue;
      if (!ON_BOARD(pos) || move[pos].final_value == 0.0)
	continue;

      if (this_value > best_value) {
	if (is_legal(pos, color) || is_illegal_ko_capture(pos, color)) {
	  best_value = this_value;
	  best_move = pos;
	}
	else {
	  TRACE("Move at %1m would be suicide.\n", pos);
	  remove_top_move(pos);
	  move[pos].value = 0.0;
	  move[pos].final_value = 0.0;
	}
      }
    }


    if (best_value > 0.0
	&& (is_illegal_ko_capture(best_move, color)
	    || !is_allowed_move(best_move, color))) {
      TRACE("Move at %1m would be an illegal ko capture.\n", best_move);
      reevaluate_ko_threats(best_move, color, best_value);
      redistribute_points();
      time_report(2, "  reevaluate_ko_threats", NO_MOVE, 1.0);
      remove_top_move(best_move);
      move[best_move].value = 0.0;
      move[best_move].final_value = 0.0;
      print_top_moves();
      good_move_found = 0;
    }


    else if (best_value > 0.0) {
      if (!blunder_tested[best_move]) {
	float blunder_size = value_moves_get_blunder_size(best_move, color);
	if (blunder_size > 0.0) {
	  TRACE("Move at %1m is a blunder, subtracting %f.\n", best_move,
		blunder_size);
	  remove_top_move(best_move);
	  move[best_move].value -= blunder_size;
	  move[best_move].final_value -= blunder_size;
	  TRACE("Move at %1m is now valued %f.\n", best_move,
		move[best_move].final_value);
	  record_top_move(best_move, move[best_move].final_value);
	  good_move_found = 0;
	  blunder_tested[best_move] = 1;
	}
	else
	  good_move_found = 1;
      }
      else
	good_move_found = 1;
    }
    else
      good_move_found = 1;
  }

  if (best_value > 0.0
      && best_move != NO_MOVE) {
    *the_move = best_move;
    *value = best_value;
    return 1;
  }

  return 0;
}
