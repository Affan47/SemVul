autohelperfusekipat125(int trans, int move, int color, int action)
{
  int a, b, c, d, e, f;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(905, trans, move);
  b = AFFINE_TRANSFORM(942, trans, move);
  c = AFFINE_TRANSFORM(906, trans, move);
  d = AFFINE_TRANSFORM(943, trans, move);
  e = AFFINE_TRANSFORM(641, trans, move);
  f = AFFINE_TRANSFORM(678, trans, move);

  return somewhere(color, 0, 4, a, b, c, d) && somewhere(color, 0, 2, e, f);
}
