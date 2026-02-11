game_position_x_is_move_legal (const GamePositionX *const gpx,
                               const Square move)
{
  g_assert(gpx);
  g_assert(square_is_valid_move(move));

  Board board;
  board.blacks = gpx->blacks;
  board.whites = gpx->whites;

  return board_is_move_legal(&board, move, gpx->player);
}
