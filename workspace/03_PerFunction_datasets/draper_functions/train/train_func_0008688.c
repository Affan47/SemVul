undo_null_move(const UndoInfo &u) {
  assert(this->is_ok());
  assert(!this->is_check());


  lastMove = u.lastMove;
  epSquare = u.epSquare;
  if(epSquare != SQ_NONE)
    key ^= zobEp[epSquare];


  sideToMove = opposite_color(sideToMove);
  rule50--;
  gamePly--;
  key ^= zobSideToMove;

  mgValue += (sideToMove == WHITE)? TempoValueMidgame : -TempoValueMidgame;
  egValue += (sideToMove == WHITE)? TempoValueEndgame : -TempoValueEndgame;

  assert(this->is_ok());
}
