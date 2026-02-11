propagate_worm(int pos)
{
  int k;
  int num_stones;
  int stones[MAX_BOARD * MAX_BOARD];
  gg_assert(stackp == 0);
  ASSERT1(IS_STONE(board[pos]), pos);

  num_stones = findstones(pos, MAX_BOARD * MAX_BOARD, stones);
  for (k = 0; k < num_stones; k++)
    if (stones[k] != pos)
      worm[stones[k]] = worm[pos];
}
