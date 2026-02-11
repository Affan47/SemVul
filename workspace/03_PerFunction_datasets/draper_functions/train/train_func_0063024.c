autohelperowl_defendpat402(int trans, int move, int color, int action)
{
  int b, c, d, A;
  UNUSED(color);
  UNUSED(action);

  b = AFFINE_TRANSFORM(685, trans, move);
  c = AFFINE_TRANSFORM(686, trans, move);
  d = AFFINE_TRANSFORM(649, trans, move);
  A = AFFINE_TRANSFORM(647, trans, move);

  return countlib(A) == 1&& (owl_escape_value(b) + owl_escape_value(c) + owl_escape_value(d)) > 0;
}
