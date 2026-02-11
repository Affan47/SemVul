find_influence_patterns(struct influence_data *q)
{
  int ii;

  current_influence = q;
  matchpat(influence_callback, ANCHOR_COLOR, &influencepat_db, q, NULL);
  if (q->color_to_move != EMPTY)
    matchpat(influence_callback, q->color_to_move, &barrierspat_db, q, NULL);

  if (q->is_territorial_influence)
    add_marked_intrusions(q);


  for (ii = BOARDMIN; ii < BOARDMAX; ii++)
    if (ON_BOARD(ii) && !q->safe[ii]) {
      int k;
      float black_reduction = 1.0;
      float white_reduction = 1.0;
      for (k = 0; k < 8; k++) {
	int d = delta[k];
	if (IS_STONE(board[ii + d]) && q->safe[ii + d]) {

	  float reduction = (k < 4) ? 0.25 : 0.65;
	  if (board[ii + d] == BLACK)
	    white_reduction *= reduction;
	  else
	    black_reduction *= reduction;
	}
	else if (IS_STONE(board[ii + d]) && !q->safe[ii + d]) {
	  if (board[ii + d] == BLACK)
	    white_reduction = -100.0;
	  else
	    black_reduction = -100.0;
	}
      }
      if (black_reduction > 0.0)
	q->black_permeability[ii] *= black_reduction;
      if (white_reduction > 0.0)
	q->white_permeability[ii] *= white_reduction;
    }

  reset_unblocked_blocks(q);
}
