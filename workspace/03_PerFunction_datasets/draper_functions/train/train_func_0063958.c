remove_move_reason(int pos, int type, int what)
{
  int k;
  int n = -1;

  ASSERT_ON_BOARD1(pos);
  for (k = 0; k < MAX_REASONS; k++) {
    int r = move[pos].reason[k];
    if (r < 0)
      break;
    if (move_reasons[r].type == type
	&& move_reasons[r].what == what)
      n = k;
  }

  if (n == -1)
    return;


  k--;
  move[pos].reason[n] = move[pos].reason[k];
  move[pos].reason[k] = -1;
}
