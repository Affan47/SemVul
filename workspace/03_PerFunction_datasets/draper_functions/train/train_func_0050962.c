influence_delta_territory(const struct influence_data *base,
    			  const struct influence_data *q, int color,
			  int move)
{
  int ii;
  float total_delta = 0.0;
  float this_delta;
  ASSERT_ON_BOARD1(move);
  ASSERT1(IS_STONE(color), move);

  for (ii = BOARDMIN; ii < BOARDMAX; ii++)
    if (ON_BOARD(ii)) {
      float new_value = q->territory_value[ii];
      float old_value = base->territory_value[ii];
      this_delta = new_value - old_value;

      if (color == BLACK) {
	new_value = -new_value;
	old_value = -old_value;
	this_delta = -this_delta;
      }

      if (move != -1
	  && (this_delta > 0.02 || -this_delta > 0.02))
	DEBUG(DEBUG_TERRITORY,
	      "  %1m:   - %1m territory change %f (%f -> %f)\n",
	      move, ii, this_delta, old_value, new_value);
      total_delta += this_delta;
    }


  this_delta = q->captured - base->captured;
  if (color == BLACK)
    this_delta = -this_delta;
  if (move != -1
      && this_delta != 0.0)
    DEBUG(DEBUG_TERRITORY, "  %1m:   - captured stones %f\n",
	  move, this_delta);
  total_delta += this_delta;

  return total_delta;
}
