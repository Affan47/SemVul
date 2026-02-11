draw_active_area(Intersection board[BOARDMAX], int apos)
{
  int i, j, ii;
  int c = ' ';
  int cw = (apos == NO_MOVE) ? 'O' : 'o';
  int cb = (apos == NO_MOVE) ? 'X' : 'x';

  start_draw_board();

  for (i = 0; i < board_size; i++) {
    ii = board_size - i;
    fprintf(stderr, "\n%2d", ii);

    for (j = 0; j < board_size; j++) {
      int pos = POS(i, j);
      if (board[pos] == EMPTY)
	c = '.';
      else if (board[pos] == WHITE)
	c = cw;
      else if ((board[pos] & 3) == WHITE)
	c = 'O';
      else if (board[pos] == BLACK)
	c = cb;
      else if ((board[pos] & 3) == BLACK)
	c = 'X';
      if (board[pos] == GRAY)
	c = '?';

      if (pos == apos)
	fprintf(stderr, "[%c", c);
      else if (j > 0 && POS(i, j-1) == apos)
	fprintf(stderr, "]%c", c);
      else
	fprintf(stderr, " %c", c);
    }

    fprintf(stderr, " %d", ii);
  }

  end_draw_board();
}
