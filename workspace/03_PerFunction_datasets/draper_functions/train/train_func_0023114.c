pentas (struct board *board, short x, short y, short side)
{
  if (board->stack[x] >= y)
    return NO;
  if (board->stack[x + 2] >= y)
    return NO;
  if (board->stack[x + 4] >= y)
    return NO;

  if (board->square[ELM (x + 1, y)] != side)
    return NO;
  if (board->square[ELM (x + 3, y)] != side)
    return NO;

  return YES;
}
