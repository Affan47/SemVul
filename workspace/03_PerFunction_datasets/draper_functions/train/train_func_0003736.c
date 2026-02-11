reset_unblocked_blocks(struct influence_data *q)
{
  int pos;
  for (pos = BOARDMIN; pos < BOARDMAX; pos++)
    if (ON_BOARD(pos)) {
      if (!q->safe[pos] && q->white_strength[pos] > 0.0
	  && q->white_permeability[pos] != 1.0) {
	DEBUG(DEBUG_INFLUENCE, "  black block removed from %1m\n", pos);
	q->white_permeability[pos] = 1.0;
      }
      if (!q->safe[pos] && q->black_strength[pos] > 0.0
	  && q->black_permeability[pos] != 1.0) {
	DEBUG(DEBUG_INFLUENCE, "  white block removed from %1m\n", pos);
	q->black_permeability[pos] = 1.0;
      }
    }
}
