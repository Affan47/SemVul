autohelperconn20(int trans, int move, int color, int action)
{
  int a, b, c, d;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(722, trans, move);
  b = AFFINE_TRANSFORM(723, trans, move);
  c = AFFINE_TRANSFORM(684, trans, move);
  d = AFFINE_TRANSFORM(724, trans, move);

  return (whose_moyo(OPPOSITE_INFLUENCE(color), a) == color) && (whose_moyo(OPPOSITE_INFLUENCE(color), b) == color) && countlib(c)>=4 && countlib(d)>=4;
}
