continueSolving(void)
{
  struct puzzle *nextpuz;
  int i, j;
  int movedPiece;
  int movedir;
  int fromx, fromy;
  int tox, toy;

  if (startPuzzle == NULL)
    return 0;
  if (startPuzzle->solnptr == NULL) {
    freeSolutions();
    return 0;
  }
  nextpuz = startPuzzle->solnptr;
  movedPiece = 0;
  movedir = 0;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      if (startPuzzle->pieces[i][j] != nextpuz->pieces[i][j]) {
        if (startPuzzle->pieces[i][j]) {
          movedPiece = startPuzzle->pieces[i][j];
          fromx = j;
          fromy = i;
          if (i < HEIGHT - 1 && nextpuz->pieces[i + 1][j] == movedPiece) {
            movedir = 3;
          } else {
            movedir = 2;
          }
          goto found_piece;
        } else {
          movedPiece = nextpuz->pieces[i][j];
          if (i < HEIGHT - 1 &&
            startPuzzle->pieces[i + 1][j] == movedPiece) {
            fromx = j;
            fromy = i + 1;
            movedir = 1;
          } else {
            fromx = j + 1;
            fromy = i;
            movedir = 0;
          }
          goto found_piece;
        }
      }
    }
  }
  glutSetWindowTitle((char *)"What!  No change?");
  freeSolutions();
  return 0;

found_piece:
  if (!movingPiece) {
    movingPiece = movedPiece;
    move_x = fromx;
    move_y = fromy;
  }
  move_x += xadds[movedir] * MOVE_SPEED;
  move_y += yadds[movedir] * MOVE_SPEED;

  tox = fromx + xadds[movedir];
  toy = fromy + yadds[movedir];

  if (move_x > tox - MOVE_SPEED / 2 && move_x < tox + MOVE_SPEED / 2 &&
    move_y > toy - MOVE_SPEED / 2 && move_y < toy + MOVE_SPEED / 2) {
    startPuzzle = nextpuz;
    movingPiece = 0;
  }
  memcpy(thePuzzle, startPuzzle->pieces, HEIGHT * WIDTH);
  changeState();
  return 1;
}
