autohelperendpat87(int trans, int move, int color, int action)
{
  int b, A;
  UNUSED(color);
  UNUSED(action);

  b = AFFINE_TRANSFORM(722, trans, move);
  A = AFFINE_TRANSFORM(758, trans, move);

  return  (whose_moyo(OPPOSITE_INFLUENCE(color), b) == color) && countlib(A)==2;
}
