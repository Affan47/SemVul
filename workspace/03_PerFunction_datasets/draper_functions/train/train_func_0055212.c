incStockCount(piece p) {
  int i;
  piece k,c;

  k=p&PIECE_MASK;
  c=p&COLOR_MASK;

  if (p&WASPAWN) k=PAWN;

  switch(k) {
  case PAWN:   i=0; break;
  case ROOK:   i=1; break;
  case KNIGHT: i=2; break;
  case BISHOP: i=3; break;
  case QUEEN:  i=4; break;
  default: return;
  }
  House[i][c==WHITE?0:1]++;


}
