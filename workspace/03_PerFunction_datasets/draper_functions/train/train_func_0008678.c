game_position_x_has_any_player_any_legal_move (const GamePositionX *const gpx)
{
  g_assert(gpx);

  const SquareSet empties = game_position_x_empties(gpx);
  const SquareSet blacks = gpx->blacks;
  const SquareSet whites = gpx->whites;

  for (Direction dir = NW; dir <= SE; dir++) {
    SquareSet wave;
    int shift;
    wave = direction_shift_square_set(dir, empties) & whites;
    shift = 1;
    while (wave != empty_square_set) {
      wave = direction_shift_square_set(dir, wave);
      shift++;
      if ((wave & blacks) != empty_square_set) return TRUE;
      wave &= whites;
    }
    wave = direction_shift_square_set(dir, empties) & blacks;
    shift = 1;
    while (wave != empty_square_set) {
      wave = direction_shift_square_set(dir, wave);
      shift++;
      if ((wave & whites) != empty_square_set) return TRUE;
      wave &= blacks;
    }
  }
  return FALSE;
}
