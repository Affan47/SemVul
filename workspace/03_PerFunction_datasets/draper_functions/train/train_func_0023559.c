monte_carlo_genmove(int color, int allowed_moves[BOARDMAX],
		    float *value, int *resign)
{
  int pos;
  int best_move = PASS_MOVE;
  int best_uct_move = PASS_MOVE;
  int unconditional_territory_black[BOARDMAX];
  int unconditional_territory_white[BOARDMAX];
  int forbidden_move[BOARDMAX];
  float move_values[BOARDMAX];
  int move_frequencies[BOARDMAX];
  float best_value;
  int frequency_cutoff;
  int frequency_cutoff2;
  int number_of_simulations;

  memset(move_values, 0, sizeof(move_values));
  memset(move_frequencies, 0, sizeof(move_frequencies));

  if (0) {
    simple_showboard(stderr);
    gprintf("\n");
  }

  if (resign)
    *resign = 0;

  unconditional_life(unconditional_territory_black, BLACK);
  unconditional_life(unconditional_territory_white, WHITE);

  for (pos = BOARDMIN; pos < BOARDMAX; pos++)
    if (!ON_BOARD(pos))
      continue;
    else if (unconditional_territory_black[pos])
      forbidden_move[pos] = BLACK;
    else if (unconditional_territory_white[pos])
      forbidden_move[pos] = WHITE;
    else
      forbidden_move[pos] = 0;

  number_of_simulations = mc_games_per_level * gg_max(get_level(), 1);

  uct_genmove(color, &best_uct_move, forbidden_move, allowed_moves,
	      number_of_simulations, move_values, move_frequencies);

  best_move = best_uct_move;
  best_value = 0.0;
  frequency_cutoff = move_frequencies[best_uct_move] / 2;
  frequency_cutoff2 = move_frequencies[best_uct_move] / 10;
  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    if (ON_BOARD(pos)
	&& (move_frequencies[pos] > frequency_cutoff
	    || (move_values[pos] > 0.9
		&& move_frequencies[pos] > frequency_cutoff2)
	    || move_values[best_uct_move] < 0.1)
	&& (!allowed_moves || allowed_moves[pos])
	&& potential_moves[pos] > best_value) {
      best_move = pos;
      best_value = potential_moves[pos];
    }
  }

  unconditionally_meaningless_move(best_move, color, &best_move);

  *value = 1.0;

  return best_move;
}
