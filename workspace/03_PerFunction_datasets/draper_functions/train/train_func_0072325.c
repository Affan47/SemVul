rotate1(int pos, int rot)
{
  int bs = board_size - 1;
  int i = I(pos);
  int j = J(pos);
  gg_assert(rot >= 0 && rot < 8);

  if (pos == PASS_MOVE)
    return PASS_MOVE;

  if (rot == 0)
    return pos;
  if (rot == 1)
    return POS(bs - j, i);
  if (rot == 2)
    return POS(bs - i, bs - j);
  if (rot == 3)
    return POS(j, bs - i);
  if (rot == 4)
    return POS(j, i);
  if (rot == 5)
    return POS(bs - i, j);
  if (rot == 6)
    return POS(bs - j, bs - i);
  if (rot == 7)
    return POS(i, bs - j);

  return PASS_MOVE;
}
