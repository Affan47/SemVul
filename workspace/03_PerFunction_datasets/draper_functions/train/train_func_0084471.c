compute_followup_influence(const struct influence_data *base,
    			   struct influence_data *q,
			   int move, const char *trace_message)
{
  int ii;
  signed char goal[BOARDMAX];

  int color = OTHER_COLOR(base->color_to_move);
  int save_debug = debug;

  memcpy(q, base, sizeof(*q));
  ASSERT1(IS_STONE(q->color_to_move), move);
  q->color_to_move = color;


  for (ii = BOARDMIN; ii < BOARDMAX; ii++)
    if (ON_BOARD(ii)) {
      if (q->safe[ii] == INFLUENCE_SAVED_STONE)
        goal[ii] = 1;
      else
	goal[ii] = 0;
    }


  if ((move == NO_MOVE
       && !(printmoyo & PRINTMOYO_INITIAL_INFLUENCE))
      || (move != debug_influence))
    debug = debug &~ DEBUG_INFLUENCE;

  q->intrusion_counter = 0;
  current_influence = q;

  matchpat_goal_anchor(followup_influence_callback, color, &barrierspat_db,
           	       q, goal, 1);

  debug = save_debug;


  add_marked_intrusions(q);

  reset_unblocked_blocks(q);


  for (ii = BOARDMIN; ii < BOARDMAX; ii++)
    if (ON_BOARD(ii))
      if ((color == BLACK
            && q->black_strength[ii] > base->black_strength[ii])
          || (color == WHITE
              && q->white_strength[ii] > base->white_strength[ii]))
        accumulate_influence(q, ii, color);

  value_territory(q);

  if (debug_influence && debug_influence == move)
    print_influence(q, trace_message);
}
