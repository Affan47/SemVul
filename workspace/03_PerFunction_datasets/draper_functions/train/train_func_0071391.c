check_men (struct board *board, short group, short side)
{
  short x, p1 = 0, p2 = 0, fx, fy;


  for (x = 0; x < TILES; x++) {
    fx = board->xplace[group][x];
    fy = board->yplace[group][x];

    if (board->square[ELM (fx, fy)] == side)
      p1++;
    else if (board->square[ELM (fx, fy)] == EMPTY)
      p2++;
  }

  return ((p1 + p2 == 4) ? p1 : -1);
}
