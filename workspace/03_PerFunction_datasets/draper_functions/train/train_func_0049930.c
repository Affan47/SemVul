generate_captures(const Position &pos, MoveStack *mlist) {
  Color us = pos.side_to_move();
  Bitboard target = pos.pieces_of_color(opposite_color(us));
  int n = 0;

  assert(pos.is_ok());
  assert(!pos.is_check());

  if(us == WHITE)
    n += generate_white_pawn_captures(pos, mlist);
  else
    n += generate_black_pawn_captures(pos, mlist);
  n += generate_knight_moves(pos, mlist+n, us, target);
  n += generate_bishop_moves(pos, mlist+n, us, target);
  n += generate_rook_moves(pos, mlist+n, us, target);
  n += generate_queen_moves(pos, mlist+n, us, target);
  n += generate_king_moves(pos, mlist+n, pos.king_square(us), target);

  return n;
}
