neighbor_of_dragon(int pos, int origin)
{
  int k;
  if (pos == NO_MOVE)
    return 0;

  for (k = 0; k < 4; k++)
    if (ON_BOARD(pos + delta[k]) && dragon[pos + delta[k]].origin == origin)
      return 1;

  return 0;
}
